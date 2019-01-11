/*
 * set policy to hmp thresholds.
 *
 * Copyright (c) 2014 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


#include <linux/mm.h>
#include <linux/vmalloc.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/delay.h>
#include <linux/thread_info.h>
#include <linux/kthread.h>
#include <linux/sysfs.h>
#include <linux/spinlock.h>
#include <linux/mutex.h>
#include <trace/events/sched.h>
#include <linux/cyclox_cfg.h>
#include "honorcfg_main.h"

/* Flag to disable/enable darkness mod (disable backlight at lowest brightness setting) */
unsigned int darkness_mod_enable = 1;

/* Flag to disable/enable overclocking and force 2362000 as scaling_max_freq for big cluster cpus */
unsigned int overclock_enable = 0;

/* Flags for usb fastcharge */
unsigned int fastcharge_enable = 1;
unsigned int fastcharge_usb_limit = USB_FASTCHARGE_CURRENT_LIMIT;
unsigned int fastcharge_chg_limit = USB_FASTCHARGE_CHARGE_LIMIT;

int isDarknessModEnabled(void) {
	return darkness_mod_enable;
}
EXPORT_SYMBOL_GPL(isDarknessModEnabled);

int isOverclockEnabled(void) {
	return overclock_enable;
}
EXPORT_SYMBOL_GPL(isOverclockEnabled);

int isFastchargeEnabled(void) {
	return fastcharge_enable;
}
EXPORT_SYMBOL_GPL(isFastchargeEnabled);

static ssize_t darkness_mod_enable_show(struct kobject *kobj,
		struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, (unsigned long)16,"%u\n", darkness_mod_enable);
}

static ssize_t darkness_mod_enable_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t n)
{
	unsigned int input;
	int ret;
	ret = sscanf(buf, "%u", &input);
	if (ret != 1 || input > 1)
		return -EINVAL;
	if (darkness_mod_enable != input) {
		darkness_mod_enable = input;
	}
	return ret;
}

static ssize_t overclock_enable_show(struct kobject *kobj,
		struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, (unsigned long)16,"%u\n", overclock_enable);
}

static ssize_t overclock_enable_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t n)
{
	unsigned int input;
	int ret;
	ret = sscanf(buf, "%u", &input);
	if (ret != 1 || input > 1)
		return -EINVAL;
	if (overclock_enable != input) {
		overclock_enable = input;
	}
	return ret;
}

static ssize_t fastcharge_enable_show(struct kobject *kobj,
		struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, (unsigned long)16,"%u\n", fastcharge_enable);
}

static ssize_t fastcharge_enable_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t n)
{
	unsigned int input;
	int ret;
	ret = sscanf(buf, "%u", &input);
	if (ret != 1 || input > 1)
		return -EINVAL;
	if (fastcharge_enable != input) {
		fastcharge_enable = input;
	}
	setFastcharge(fastcharge_enable, fastcharge_usb_limit, fastcharge_chg_limit);
	return ret;
}

static ssize_t fastcharge_usb_limit_show(struct kobject *kobj,
		struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, (unsigned long)16,"%u\n", fastcharge_usb_limit);
}

static ssize_t fastcharge_usb_limit_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t n)
{
	unsigned int input;
	int ret;
	ret = sscanf(buf, "%u", &input);
	if (ret != 1 || input < USB_NORMALCHARGE_CURRENT_LIMIT || input > USB_FASTCHARGE_CURRENT_LIMIT)
		return -EINVAL;
	if (fastcharge_usb_limit != input) {
		fastcharge_usb_limit = input;
	}
	setFastcharge(fastcharge_enable, fastcharge_usb_limit, fastcharge_chg_limit);
	return ret;
}

static ssize_t fastcharge_chg_limit_show(struct kobject *kobj,
		struct kobj_attribute *attr, char *buf)
{
	return snprintf(buf, (unsigned long)16,"%u\n", fastcharge_chg_limit);
}

static ssize_t fastcharge_chg_limit_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t n)
{
	unsigned int input;
	int ret;
	ret = sscanf(buf, "%u", &input);
	if (ret != 1 || input < USB_NORMALCHARGE_CHARGE_LIMIT || input > USB_FASTCHARGE_CHARGE_LIMIT)
		return -EINVAL;
	if (fastcharge_chg_limit != input) {
		fastcharge_chg_limit = input;
	}
	setFastcharge(fastcharge_enable, fastcharge_usb_limit, fastcharge_chg_limit);
	return ret;
}

static struct kobj_attribute darkness_mod_enable_attr = {
	.attr   = {
		.name = "darkness_mod_enable",
		.mode = 0664,
	},
	.show   = darkness_mod_enable_show,
	.store  = darkness_mod_enable_store,
};

static struct kobj_attribute overclock_enable_attr = {
	.attr   = {
		.name = "overclock_enable",
		.mode = 0664,
	},
	.show   = overclock_enable_show,
	.store  = overclock_enable_store,
};

static struct kobj_attribute fastcharge_enable_attr = {
	.attr   = {
		.name = "fastcharge_enable",
		.mode = 0664,
	},
	.show   = fastcharge_enable_show,
	.store  = fastcharge_enable_store,
};

static struct kobj_attribute fastcharge_usb_limit_attr = {
	.attr   = {
		.name = "fastcharge_usb_limit",
		.mode = 0664,
	},
	.show   = fastcharge_usb_limit_show,
	.store  = fastcharge_usb_limit_store,
};

static struct kobj_attribute fastcharge_chg_limit_attr = {
	.attr   = {
		.name = "fastcharge_chg_limit",
		.mode = 0664,
	},
	.show   = fastcharge_chg_limit_show,
	.store  = fastcharge_chg_limit_store,
};

static struct attribute *attrs[] = {
	&darkness_mod_enable_attr.attr,
	&overclock_enable_attr.attr,
	&fastcharge_enable_attr.attr,
	&fastcharge_usb_limit_attr.attr,
	&fastcharge_chg_limit_attr.attr,
	NULL
};

static struct attribute_group honorcfg_attr_group = {
	.attrs = attrs,
};

struct kobject *honorcfg_kobj;

static int create_sysfs_node(void)
{
	int retval;

	/* wait for kernel_kobj node ready: */
	while (kernel_kobj == NULL)
		msleep(100);

	/* Create kobject named "honorcfg",located under /sys/kernel/ */
	honorcfg_kobj = kobject_create_and_add("honorcfg", kernel_kobj);
	if (!honorcfg_kobj)
		return -ENOMEM;

	/* Create the files associated with this kobject */
	retval = sysfs_create_group(honorcfg_kobj, &honorcfg_attr_group);
	if (retval)
		kobject_put(honorcfg_kobj);
	return retval;
}

static int __init honorcfg_init(void)
{
	int ret;

	/*
	 * init sysfs_node
	 */
	ret = create_sysfs_node();
	if (ret)
		pr_err("honorcfg: create_sysfs_node fail.\n");

	return 0;
}

module_init(honorcfg_init);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("cyclon1978 <cyclon1978@web.de>");
MODULE_DESCRIPTION("configure honor advanced kernel features");

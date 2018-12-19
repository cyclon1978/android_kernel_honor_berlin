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
#include "honorcfg_main.h"

/* Flag to disable/enable darkness mod (disable backlight at lowest brightness setting) */
unsigned int darkness_mod_enable = 1;

/* Flag to disable/enable overclocking and force 2362000 as scaling_max_freq for big cluster cpus */
unsigned int overclock_enable = 0;

int isDarknessModEnabled(void) {
	return darkness_mod_enable;
}
EXPORT_SYMBOL_GPL(isDarknessModEnabled);

int isOverclockEnabled(void) {
	return overclock_enable;
}
EXPORT_SYMBOL_GPL(isOverclockEnabled);

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

static struct attribute *attrs[] = {
	&darkness_mod_enable_attr.attr,
	&overclock_enable_attr.attr,
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

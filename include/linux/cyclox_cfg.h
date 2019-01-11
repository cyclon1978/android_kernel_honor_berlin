/*
 * configure advanced kernel features.
 *
 * Copyright (c) 2014 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef        __CYCLOXCFG_MAIN_H_
#define __CYCLOXCFG_MAIN_H_

#include <linux/types.h>

#ifdef CONFIG_HUAWEI_LCD_PANEL_DARKNESS_MOD
int isDarknessModEnabled(void);
#endif

#ifdef CONFIG_OVERCLOCK_AS_KIRIN_655
int isOverclockEnabled(void);
#endif

#ifdef CONFIG_USB_FASTCHARGE

#define USB_FASTCHARGE_CURRENT_LIMIT   900
#define USB_FASTCHARGE_CHARGE_LIMIT    686

#define USB_NORMALCHARGE_CURRENT_LIMIT 500
#define USB_NORMALCHARGE_CHARGE_LIMIT  500

void setFastcharge(bool active, int usb_limit, int chg_limit);

int isFastchargeEnabled(void);

#endif

#endif /* End #define __CYCLOXCFG_MAIN_H_ */


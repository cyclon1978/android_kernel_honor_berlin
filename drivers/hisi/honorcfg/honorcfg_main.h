/*
 * set policy to hmp thresholds.
 *
 * Copyright (c) 2014 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef	__HONORCFG_MAIN_H_
#define __HONORCFG_MAIN_H_

#include <linux/types.h>

#ifdef HONORCFG_SET_DEBUG
#define honorcfg_debug(fmt, ...) pr_err(fmt, ...)
#else
#define honorcfg_debug(fmt, ...) {}
#endif


#endif	/* End #define __HONORCFG_MAIN_H_ */

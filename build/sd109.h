/*
 * sd109.h - Part of OPEN-EYES-II products, Linux kernel modules for hardware
 * monitoring
 *
 * Author:
 * Massimiliano Negretti <massimiliano.negretti@open-eyes.it> 2020-07-12
 *
 * Include file of sd109-hwmon Linux driver
 *
 * This file is part of sd109-hwmon distribution
 * https://github.com/openeyes-lab/sd109-hwmon
 *
 * Copyright (c) 2021 OPEN-EYES Srl 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef _SD109_H
#define _SD109_H

#include <linux/regmap.h>
#include <linux/rtc.h>
#include <linux/time64.h>
#include <linux/watchdog.h>

struct device;

#define NUM_CH_VIN                      5

struct sd109_private {
  struct i2c_client	            *client;
  struct regmap		              *regmap;
  struct watchdog_device        wdd;
  struct rtc_device	            *rtc;
  bool                          overlay_wdog_nowayout;
  int                           overlay_wdog_timeout;
  int                           overlay_wdog_wait;
  int                           device_wdog_timeout;
  int                           device_wdog_wait;
  int                           wdog_wait;
	struct mutex                  update_lock;
  u16                           firmware_version;
  bool                          alarm_enabled;
  bool                          alarm_pending;
	/* Voltage registers */
  bool volt_valid[NUM_CH_VIN];
	u16 volt[NUM_CH_VIN];
  unsigned long volt_updated[NUM_CH_VIN];
  /* Voltage max registers */
  bool volt_max_valid[NUM_CH_VIN];
	u16 volt_max[NUM_CH_VIN];
  unsigned long volt_max_updated[NUM_CH_VIN];
  /* Voltage min registers */
  bool volt_min_valid[NUM_CH_VIN];
	u16 volt_min[NUM_CH_VIN];
  unsigned long volt_min_updated[NUM_CH_VIN];
};

#define SD109_NUM_REGS                  32

#define SD109_CHIP_ID_REG               0x00
#define SD109_CHIP_ID                   0xd109
#define SD109_CHIP_VER_REG              0x01

#define SD109_STATUS                    0x02
#define SD109_STATUS_POWERUP            0x0001
#define SD109_STATUS_POWEROFF           0x0002
#define SD109_STATUS_REBOOT             0x0003
#define SD109_STATUS_HALT               0x0004
#define SD109_STATUS_WAKEUP             0x0005
#define SD109_STATUS_BOOT_MASK          0x0007
#define SD109_STATUS_WDOG_EN            0x0008

#define SD109_COMMAND                   0x06
#define SD109_WDOG_ENABLE               0x01
#define SD109_WDOG_DISABLE              0x02
#define SD109_EXEC_POWEROFF             0x03
#define SD109_EXEC_REBOOT               0x04
#define SD109_EXEC_HALT                 0x05

#define SD109_WDOG_REFRESH              0x08
#define SD109_WDOG_REFRESH_MAGIC_VALUE  0x0d1e
#define SD109_WDOG_TIMEOUT              0x09
#define SD109_WDOG_TIMEOUT_MASK         0x00FF
#define SD109_WDOG_TIMEOUT_POS          0
#define SD109_WDOG_WAIT_MASK            0xFF00
#define SD109_WDOG_WAIT_POS             8

#define SD109_VOLTAGE_5V_BOARD          0x0A
#define SD109_VOLTAGE_5V_BOARD_MIN      0x0B
#define SD109_VOLTAGE_5V_BOARD_MAX      0x0C
#define SD109_VOLTAGE_5V_RPI            0x0D
#define SD109_VOLTAGE_3V3_RPI           0x10
#define SD109_VOLTAGE_1V8_RPI           0x13
#define SD109_VOLTAGE_12V_BOARD         0x16

#define SD109_RTC0                      0x1A
#define SD109_RTC1                      0x1B
#define SD109_RTC2                      0x1C
#define SD109_WAKEUP0                   0x1D
#define SD109_WAKEUP1                   0x1E
#define SD109_WAKEUP2                   0x1F

#define SD109_MIN_WDOG_WAIT             45

#endif /* _SD109_H */

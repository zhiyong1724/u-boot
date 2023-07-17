/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2021, STMicroelectronics - All Rights Reserved
 * Author(s): CHENZHIYONG <172471067@qq.com>
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <config.h>
#include <linux/sizes.h>

/* For booting Linux, use the first 16MB of memory */
#define CONFIG_SYS_BOOTMAPSZ		(SZ_16M + SZ_8M)

#define CONFIG_SYS_FLASH_BASE		0x90000000
#define CONFIG_SYS_INIT_SP_ADDR		0x20020000

/*
 * Configuration of the external SDRAM memory
 */
#define CONFIG_SYS_LOAD_ADDR		0xC2000000
#define CONFIG_LOADADDR			0xC2000000

#define CONFIG_SYS_HZ_CLOCK		1000000

#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_REVISION_TAG

#define CONFIG_SYS_MAXARGS		16
#define CONFIG_SYS_MALLOC_LEN		(256 * 1024)

#define BOOT_TARGET_DEVICES(func) \
	func(MMC, mmc, 0)

#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE 0x90000000
#define CONFIG_BOOTCOMMAND \
	"sf probe; " \
	"setenv image_load_addr 0xc3000000; " \
	"setenv offset 0x200000; " \
	"setenv index 0; " \
	"setenv temp 0; " \
	"while itest ${index} < 0x600000; " \
	"do " \
	"setexpr temp ${image_load_addr} + ${index}; " \
	"sf read ${temp} ${offset} 0x8000; " \
	"setexpr offset ${offset} + 0x8000; " \
	"setexpr index ${index} + 0x8000; " \
	"done; " \
	"setexpr temp ${image_load_addr} + 0x2c0; " \
	"go ${temp}; "

/* #include <config_distro_bootcmd.h>
#define CONFIG_EXTRA_ENV_SETTINGS				\
			"kernel_addr_r=0xC0008000\0"		\
			"fdtfile=stm32h750-nand.dtb\0"	\
			"fdt_addr_r=0xC0408000\0"		\
			"scriptaddr=0xC0418000\0"		\
			"pxefile_addr_r=0xC0428000\0" \
			"ramdisk_addr_r=0xC0438000\0"		\
			BOOTENV */

#endif /* __CONFIG_H */

// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2023, STMicroelectronics - All Rights Reserved
 * Author(s): CHENZHIYONG <172471067@qq.com>
 */

#include <common.h>
#include <dm.h>
#include <init.h>
#include <log.h>
#include <asm/global_data.h>
#include <asm/armv7_mpu.h>
DECLARE_GLOBAL_DATA_PTR;
#define CPACR (*((volatile uint32_t *)0xe000ed88))
int dram_init(void)
{
	struct udevice *dev;
	int ret;

	ret = uclass_get_device(UCLASS_RAM, 0, &dev);
	if (ret) {
		debug("DRAM init failed: %d\n", ret);
		return ret;
	}

	if (fdtdec_setup_mem_size_base() != 0)
		ret = -EINVAL;
	return ret;
}

int dram_init_banksize(void)
{
	fdtdec_setup_memory_banksize();

	return 0;
}

int board_early_init_f(void)
{
	return 0;
}

u32 get_board_rev(void)
{
	return 0;
}

int board_late_init(void)
{
	return 0;
}

int board_init(void)
{
	gd->bd->bi_boot_params = gd->bd->bi_dram[0].start + 0x100;
	return 0;
}

int mach_cpu_init(void)
{
	int i;
	CPACR |= ((3UL << (10*2))|(3UL << (11*2)));  /* set CP10 and CP11 Full Access */
	struct mpu_region_config stm32_region_config[] = {
		/*
		 * Make SDRAM area cacheable & executable.
		 */
		{ 0x20000000, REGION_0, XN_DIS, PRIV_RW_USR_RW,
		O_I_NON_CACHEABLE, REGION_512MB },

		{ 0x40000000, REGION_1, XN_DIS, PRIV_RW_USR_RW,
		DEVICE_NON_SHARED, REGION_512MB },

		{ 0x80000000, REGION_2, XN_DIS, PRIV_RW_USR_RW,
		DEVICE_NON_SHARED, REGION_256MB },

		{ 0xC0000000, REGION_3, XN_DIS, PRIV_RW_USR_RW,
		O_I_WB_RD_WR_ALLOC, REGION_512MB },
	};

	disable_mpu();
	for (i = 0; i < ARRAY_SIZE(stm32_region_config); i++)
		mpu_config(&stm32_region_config[i]);
	enable_mpu();
	return 0;
}

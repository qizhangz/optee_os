/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2015, Linaro Limited
 */

#ifndef PLATFORM_CONFIG_H
#define PLATFORM_CONFIG_H

/* Make stacks aligned to data cache line length */
#define STACK_ALIGNMENT		64

#ifdef ARM64
#ifdef CFG_WITH_PAGER
#error "Pager not supported for ARM64"
#endif
#endif /*ARM64*/

#if defined(PLATFORM_FLAVOR_mt8173)

#define GIC_BASE		0x10220000
#define GICC_OFFSET		0x2000
#define GICD_OFFSET		0x1000

#define UART0_BASE		0x11002000
#define UART1_BASE		0x11003000
#define UART2_BASE		0x11004000
#define UART3_BASE		0x11005000

#define CONSOLE_UART_BASE	UART0_BASE
#define CONSOLE_BAUDRATE	921600
#define CONSOLE_UART_CLK_IN_HZ	26000000

#define DRAM0_BASE		0x40000000
#define DRAM0_SIZE		0x80000000

/* Location of trusted dram */
#define TZDRAM_BASE		0xBE000000
#define TZDRAM_SIZE		0x02000000

#define CFG_TEE_CORE_NB_CORE	4

/* Full GlobalPlatform test suite requires CFG_SHMEM_SIZE to be at least 2MB */
#define CFG_SHMEM_START		(TZDRAM_BASE - 0x200000)
#define CFG_SHMEM_SIZE		0x200000

#else
#error "Unknown platform flavor"
#endif

#define CFG_TEE_RAM_VA_SIZE	(1024 * 1024)

#ifndef CFG_TEE_LOAD_ADDR
#define CFG_TEE_LOAD_ADDR	CFG_TEE_RAM_START
#endif

/*
 * Everything is in TZDRAM.
 * +------------------+
 * |        | TEE_RAM |
 * + TZDRAM +---------+
 * |        | TA_RAM  |
 * +--------+---------+
 */
#define CFG_TEE_RAM_PH_SIZE	CFG_TEE_RAM_VA_SIZE
#define CFG_TEE_RAM_START	TZDRAM_BASE
#define CFG_TA_RAM_START	ROUNDUP((TZDRAM_BASE + CFG_TEE_RAM_VA_SIZE), \
					CORE_MMU_DEVICE_SIZE)
#define CFG_TA_RAM_SIZE		ROUNDDOWN((TZDRAM_SIZE - CFG_TEE_RAM_VA_SIZE), \
					  CORE_MMU_DEVICE_SIZE)

#ifdef CFG_WITH_LPAE
#define MAX_XLAT_TABLES		5
#endif

#endif /*PLATFORM_CONFIG_H*/

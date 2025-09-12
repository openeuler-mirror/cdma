/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __CDMA_U_LIB_H__
#define __CDMA_U_LIB_H__
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdatomic.h>
#include <cdma_abi.h>

/* cover the maximum file length(255) + path prefix */
#define CDMA_MAX_DEV_NAME_LEN 300

struct dma_device {
	char name[CDMA_MAX_DEV_NAME_LEN];
	int fd;
	struct cdma_device_attr attr;
};

typedef enum {
	DMA_CR_OPC_SEND = 0x00,
	DMA_CR_OPC_SEND_WITH_IMM,
	DMA_CR_OPC_SEND_WITH_INV,
	DMA_CR_OPC_WRITE_WITH_IMM,
} dma_cr_opcode_t;

typedef union dma_cr_flag {
	struct {
		uint8_t s_r : 1;
		uint8_t jetty : 1;
		uint8_t suspend_done : 1;
		uint8_t flush_err_done : 1;
		uint8_t reserved : 4;
	} bs;
	uint8_t value;
} dma_cr_flag_t;

struct dma_cr {
	enum dma_cr_status	status;
	uint64_t		user_ctx;
	dma_cr_opcode_t		opcode;
	dma_cr_flag_t		flag;
	uint32_t		completion_len;
	uint32_t		local_id;
	uint32_t		remote_id;
	uint32_t		tpn;
};

struct dma_seg {
	uint64_t handle;
	uint64_t sva;
	uint64_t len;
	uint32_t tid; /* data valid only in bit 0-19 */
	uint32_t token_value;
	bool token_value_valid;
};

struct dma_context {
	struct dma_device *dma_dev;
	uint32_t tid;
	int async_fd;
};

typedef enum {
	DMA_STATUS_OK,
	DMA_STATUS_INVAL,
} dma_status;

/**
 * dma_get_device_list - Get DMA device list
 * @num_devices: DMA device number;
 * Return: address of the first device in the list
 */
struct dma_device *dma_get_device_list(uint32_t *num_devices);

/**
 * dma_free_device_list - Free DMA device list
 * @dev_list: DMA device list;
 * @num_devices: DMA device number;
 * Return: NA
 */
void dma_free_device_list(struct dma_device *dev_list, uint32_t num_devices);

/**
 * dma_get_device_by_eid - Get the specified EID DMA device
 * @eid: device eid pointer;
 * Return: DMA device structure pointer
 */
struct dma_device *dma_get_device_by_eid(struct dev_eid *eid);

/**
 * dma_create_context - Create DMA context
 * @dma_dev: DMA device pointer;
 * Return: DMA context structure pointer
 */
struct dma_context *dma_create_context(struct dma_device *dma_dev);

/**
 * dma_delete_context - Delete DMA context
 * @ctx: DMA context pointer;
 * Return: NA
 */
void dma_delete_context(struct dma_context *ctx);


#endif

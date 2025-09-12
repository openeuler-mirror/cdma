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

#endif

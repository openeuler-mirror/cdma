// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>
#include <cdma_abi.h>
#include "cdma_u_device.h"
#include "cdma_u_log.h"
#include "cdma_u_lib.h"

struct dma_device *dma_get_device_list(uint32_t *num_devices)
{
	if (!num_devices)
		return NULL;

	return cdma_get_device_list(num_devices);
}

void dma_free_device_list(struct dma_device *dev_list, uint32_t num_devices)
{
	/*
	* num_devices can be 0, it means that no device has been obtained,
	* but the dev_list memory should be free any way
	*/
	if (!dev_list) {
		return;
	}

	cdma_free_device_list(dev_list, num_devices);
}

struct dma_device *dma_get_device_by_eid(struct dev_eid *eid)
{
	if (!eid)
		return NULL;

	return cdma_get_device_by_eid(eid);
}

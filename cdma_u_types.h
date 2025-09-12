/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __CDMA_U_TYPES_H__
#define __CDMA_U_TYPES_H__

#include <stdint.h>
#include <stddef.h>
#include <pthread.h>
#include <stdatomic.h>
#include "cdma_u_lib.h"

#define DMA_EID_SIZE (16)

typedef struct dma_tp_cfg {
	uint32_t scna;
	uint32_t dcna;
	uint32_t seid;
	uint32_t deid;
	uint32_t queue_id;
} dma_tp_cfg_t;

typedef struct dma_tp {
	struct dma_context *dma_ctx;
	dma_tp_cfg_t cfg;
	uint32_t tpn;
	uint64_t handle;
} dma_tp_t;

#endif

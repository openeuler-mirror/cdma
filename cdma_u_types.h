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

typedef struct dma_jfce {
	struct dma_context	*dma_ctx;
	int			fd;
	int			id;
} dma_jfce_t;

typedef union dma_jfc_flag {
	struct {
		uint32_t    lock_free : 1;
		uint32_t    jfc_inline : 1;
		uint32_t    reserved : 30;
	} bs;
	uint32_t value;
} dma_jfc_flag_t;

typedef struct dma_jfc_cfg {
	uint32_t depth;
	dma_jfc_flag_t flag;
	uint32_t ceqn;
	dma_jfce_t *jfce;
	uint64_t user_ctx;
	uint32_t queue_id;
} dma_jfc_cfg_t;

typedef struct dma_jfc {
	struct dma_context	*dma_ctx;
	uint32_t		jfc_id;
	dma_jfc_cfg_t		jfc_cfg;
	uint64_t		handle;
	pthread_mutex_t		event_mutex;
	pthread_cond_t		event_cond;
	uint32_t		comp_events_acked;
	uint32_t		async_events_acked;
} dma_jfc_t;

#endif

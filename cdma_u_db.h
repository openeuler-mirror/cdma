/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __CDMA_U_DB_H__
#define __CDMA_U_DB_H__
#include "cdma_u_common.h"

void *cdma_u_alloc_sw_db(struct cdma_u_context *ctx);

void cdma_u_free_sw_db(struct cdma_u_context *ctx, uint32_t *db);

int cdma_u_alloc_db(struct dma_context *dma_ctx, struct cdma_u_doorbell *db);

void cdma_u_free_db(struct dma_context *dma_ctx, struct cdma_u_doorbell *db);

#endif

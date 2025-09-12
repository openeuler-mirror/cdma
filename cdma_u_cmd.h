/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __CDMA_CMD_H__
#define __CDMA_CMD_H__
#include <stdio.h>
#include "cdma_u_lib.h"
#include "cdma_u_types.h"

int cdma_cmd_create_ctp(struct dma_context *ctx, struct dma_tp *ctp,
			struct dma_tp_cfg *cfg);
int cdma_cmd_delete_ctp(struct dma_tp *ctp);
#endif

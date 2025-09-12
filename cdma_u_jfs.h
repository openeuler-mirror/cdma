/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef _CDMA_U_JFS_H_
#define _CDMA_U_JFS_H_

#include "cdma_u_lib.h"
#include "cdma_u_common.h"


#define MAX_SQE_BB_NUM 4

#define SQE_WRITE_NOTIFY_CTL_LEN 80


#define SQE_ATOMIC_DATA_FIELD 64

struct dma_jfs *cdma_u_create_jfs(struct dma_context *ctx,
				  struct dma_jfs_cfg *cfg);
int cdma_u_delete_jfs(struct dma_jfs *jfs);

#endif

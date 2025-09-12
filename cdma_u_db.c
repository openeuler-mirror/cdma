// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>
#include "cdma_u_log.h"
#include "cdma_u_db.h"

int cdma_u_alloc_db(struct dma_context *ctx, struct cdma_u_doorbell *db)
{
	struct cdma_u_context *cdma_ctx = to_cdma_u_ctx(ctx);
	off_t offset;

	offset = get_mmap_offset(db->id, cdma_ctx->page_size, db->type);
	db->addr = mmap(NULL, cdma_ctx->page_size, PROT_READ | PROT_WRITE,
			MAP_SHARED, ctx->dma_dev->fd, offset);
	if (db->addr == MAP_FAILED) {
		CDMA_LOG_ERR("mmap doorbell page failed, id = %u, type = %u.\n",
			      db->id, db->type);
		return -EINVAL;
	}

	return 0;
}

void cdma_u_free_db(struct dma_context *ctx, struct cdma_u_doorbell *db)
{
	struct cdma_u_context *cdma_ctx;

	if (db->addr == MAP_FAILED || db->addr == NULL) {
		CDMA_LOG_ERR("invalid parameter.\n");
		return;
	}

	cdma_ctx = to_cdma_u_ctx(ctx);

	munmap((void *)db->addr, (size_t)cdma_ctx->page_size);
	db->addr = NULL;
}

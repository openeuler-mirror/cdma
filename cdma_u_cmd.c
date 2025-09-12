// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include <stdint.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <stdbool.h>
#include <cdma_abi.h>
#include "cdma_u_log.h"
#include "cdma_u_cmd.h"

int cdma_cmd_create_ctp(struct dma_context *ctx, struct dma_tp *ctp,
			struct dma_tp_cfg *cfg)
{
	struct cdma_cmd_create_ctp_args arg = {0};
	struct cdma_ioctl_hdr hdr;
	int ret;

	if (!ctx || !ctx->dma_dev || ctx->dma_dev->fd < 0 || !ctp || !cfg) {
		CDMA_LOG_ERR("create ctp cmd parameter invalid.\n");
		return -EINVAL;
	}

	hdr.command = (uint32_t)CDMA_CMD_CREATE_CTP;
	hdr.args_len = (uint32_t)sizeof(arg);
	hdr.args_addr = (uint64_t)&arg;

	arg.in.scna = cfg->scna;
	arg.in.dcna = cfg->dcna;
	arg.in.seid = cfg->seid;
	arg.in.deid = cfg->deid;
	arg.in.dma_tp = (uint64_t)(void *)ctp;
	arg.in.queue_id = cfg->queue_id;

	ret = ioctl(ctx->dma_dev->fd, CDMA_SYNC, &hdr);
	if (ret != 0) {
		CDMA_LOG_ERR("ioctl execute create ctp failed, ret = %d, errno = %d, cmd = %u.\n",
			      ret, errno, hdr.command);
		return ret;
	}

	ctp->dma_ctx = ctx;
	ctp->cfg = *cfg;
	ctp->tpn = arg.out.tpn;
	ctp->handle = arg.out.handle;

	return 0;
}

int cdma_cmd_delete_ctp(struct dma_tp *ctp)
{
	struct cdma_cmd_delete_ctp_args arg = {0};
	struct cdma_ioctl_hdr hdr;
	int ret;

	if (!ctp || !ctp->dma_ctx || !ctp->dma_ctx->dma_dev ||
		ctp->dma_ctx->dma_dev->fd < 0) {
		CDMA_LOG_ERR("cdma delete ctp cmd parameter invalid.\n");
		return -EINVAL;
	}

	hdr.command = (uint32_t)CDMA_CMD_DELETE_CTP;
	hdr.args_len = (uint32_t)sizeof(arg);
	hdr.args_addr = (uint64_t)&arg;
	arg.in.tpn = ctp->tpn;
	arg.in.handle = ctp->handle;
	arg.in.queue_id = ctp->cfg.queue_id;

	ret = ioctl(ctp->dma_ctx->dma_dev->fd, CDMA_SYNC, &hdr);
	if (ret != 0) {
		CDMA_LOG_ERR("ioctl execute delete ctp failed, ret = %d, errno = %d, cmd = %u.\n",
			      ret, errno, hdr.command);
		return ret;
	}

	return 0;
}

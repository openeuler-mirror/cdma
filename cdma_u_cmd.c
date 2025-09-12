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

int cdma_cmd_create_jfce(struct dma_context *ctx, dma_jfce_t *jfce)
{
	struct cdma_cmd_create_jfce_args arg = {0};
	struct cdma_ioctl_hdr hdr = {0};
	int ret;

	if (ctx == NULL || ctx->dma_dev == NULL || ctx->dma_dev->fd < 0) {
		CDMA_LOG_ERR("create jfce cmd parameter invalid.\n");
		return -EINVAL;
	}

	hdr.command = (uint32_t)CDMA_CMD_CREATE_JFCE;
	hdr.args_len = (uint32_t)sizeof(arg);
	hdr.args_addr = (uint64_t)&arg;

	ret = ioctl(ctx->dma_dev->fd, CDMA_SYNC, &hdr);
	if (ret != 0) {
		CDMA_LOG_ERR("ioctl execute create jfce failed, ret = %d.\n", ret);
		return ret;
	}

	jfce->fd = arg.out.fd;
	jfce->id = arg.out.id;

	return 0;
}

static inline void cdma_cmd_set_udrv_priv(struct cdma_cmd_udrv_priv *arg,
					  struct cdma_cmd_udrv_priv *udata)
{
	if (arg != NULL && udata != NULL) {
		*arg = *udata;
	}
}

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

static inline void cdma_fill_jfs(struct dma_jfs *jfs, struct dma_context *ctx,
				 struct dma_jfs_cfg *cfg,
				 struct cdma_cmd_create_jfs_args *arg)
{
	jfs->jfs_id = arg->out.id;
	jfs->jfs_cfg = *cfg;
	jfs->jfs_cfg.depth = arg->out.depth;
	jfs->jfs_cfg.max_sge = arg->out.max_sge;
	jfs->jfs_cfg.max_rsge = arg->out.max_rsge;
	jfs->dma_ctx = ctx;
	jfs->handle = arg->out.handle;
}

int cdma_u_cmd_create_jfs(struct dma_context *ctx, struct dma_jfs *jfs,
			  struct dma_jfs_cfg *cfg,
			  struct cdma_cmd_udrv_priv *udata)
{
	struct cdma_cmd_create_jfs_args arg = {0};
	struct cdma_ioctl_hdr hdr;
	int ret;

	if (!ctx || !ctx->dma_dev || ctx->dma_dev->fd < 0 || !jfs ||
		!cfg || !cfg->jfc) {
		CDMA_LOG_ERR("create jfs cmd parameter invalid.\n");
		return -EINVAL;
	}

	hdr.command = (uint32_t)CDMA_CMD_CREATE_JFS;
	hdr.args_len = (uint32_t)sizeof(arg);
	hdr.args_addr = (uint64_t)&arg;

	arg.in.depth = cfg->depth;
	arg.in.flag = cfg->flag.value;
	arg.in.priority = cfg->priority;
	arg.in.max_sge = cfg->max_sge;
	arg.in.max_rsge = cfg->max_rsge;
	arg.in.rnr_retry = cfg->rnr_retry;
	arg.in.err_timeout = cfg->err_timeout;
	arg.in.jfc_id = cfg->jfc->jfc_id;
	arg.in.queue_id = cfg->queue_id;
	arg.in.rmt_eid = cfg->rmt_eid;
	arg.in.pld_token_id = cfg->pld_token_id;
	arg.in.tpn = cfg->tpn;
	arg.in.dma_jfs = (uint64_t)jfs;
	arg.in.eid_idx = cfg->eid_idx;
	cdma_cmd_set_udrv_priv(&arg.udata, udata);

	ret = ioctl(ctx->dma_dev->fd, CDMA_SYNC, &hdr);
	if (ret != 0) {
		CDMA_LOG_ERR("ioctl execute create jfs failed, ret = %d, cmd = %u.\n", ret, hdr.command);
		return -ret;
	}

	cdma_fill_jfs(jfs, ctx, cfg, &arg);

	return 0;
}

int cdma_u_cmd_delete_jfs(struct dma_jfs *jfs)
{
	struct cdma_cmd_delete_jfs_args arg = {0};
	struct cdma_ioctl_hdr hdr;
	int ret;

	if (!jfs || !jfs->dma_ctx || !jfs->dma_ctx->dma_dev ||
		jfs->dma_ctx->dma_dev->fd < 0) {
		CDMA_LOG_ERR("delete jfs cmd parameter invalid");
		return -EINVAL;
	}

	hdr.command = (uint32_t)CDMA_CMD_DELETE_JFS;
	hdr.args_len = (uint32_t)sizeof(arg);
	hdr.args_addr = (uint64_t)&arg;
	arg.in.jfs_id = jfs->jfs_id;
	arg.in.queue_id = jfs->jfs_cfg.queue_id;
	arg.in.handle = jfs->handle;

	ret = ioctl(jfs->dma_ctx->dma_dev->fd, CDMA_SYNC, &hdr);
	if (ret != 0) {
		CDMA_LOG_ERR("ioctl execute delete jfs failed, ret = %d, cmd = %u.\n", ret, hdr.command);
		return -EFAULT;
	}

	return 0;
}
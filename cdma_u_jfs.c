// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#include <string.h>
#include "cdma_u_db.h"
#include "cdma_u_log.h"
#include "cdma_u_cmd.h"
#include "cdma_u_log.h"
#include "cdma_u_jfc.h"
#include "cdma_u_jfs.h"

static int cdma_u_exec_create_jfs_cmd(struct dma_context *ctx,
				      struct cdma_u_jfs *jfs,
				      struct dma_jfs_cfg *cfg)
{
	struct cdma_create_jfs_ucmd cmd = {0};
	struct cdma_cmd_udrv_priv udata = {0};
	int ret;

	cmd.buf_addr = (uintptr_t)jfs->sq.qbuf;
	cmd.buf_len = jfs->sq.qbuf_size;
	cmd.jetty_addr = (uintptr_t)&jfs->sq;
	cmd.sqe_bb_cnt = jfs->sq.sqe_bb_cnt;
	cmd.jetty_type = jfs->jfs_type;
	cmd.queue_id = cfg->queue_id;
	cmd.non_pin = jfs->sq.cstm;
	cmd.tid = ctx->tid;
	cdma_u_set_udata(&udata, &cmd, sizeof(cmd), NULL, 0);

	ret = cdma_u_cmd_create_jfs(ctx, &jfs->base, cfg, &udata);
	if (ret) {
		CDMA_LOG_ERR("cmd create jfs failed, ret = %d.\n", ret);
	}

	return ret;
}

static inline void cdma_u_init_sq(struct cdma_u_jetty_queue *sq)
{
	sq->flush_flag = false;
	sq->pi = 0;
	sq->ci = 0;
}

static inline uint32_t cdma_sq_cal_wqebb_num(uint32_t sqe_ctl_len,
					     uint32_t sge_num,
					     uint32_t wqebb_size)
{
	return (sqe_ctl_len + (sge_num - 1) * CDMA_SGE_SIZE) / wqebb_size + 1;
}

static int cdma_u_create_sq(struct cdma_u_jetty_queue *sq,
			    struct dma_jfs_cfg *cfg)
{
	uint32_t wqebb_depth;
	uint32_t sqe_bb_cnt;

	if (pthread_spin_init(&sq->lock, PTHREAD_PROCESS_PRIVATE)) {
		CDMA_LOG_ERR("init lock failed.\n");
		return -EINVAL;
	}

	cdma_u_init_sq(sq);

	sqe_bb_cnt = cdma_sq_cal_wqebb_num(SQE_WRITE_NOTIFY_CTL_LEN,
					   cfg->max_sge, CDMA_JFS_WQEBB);
	if (sqe_bb_cnt > MAX_SQE_BB_NUM)
		sqe_bb_cnt = MAX_SQE_BB_NUM;
	sq->sqe_bb_cnt = sqe_bb_cnt;
	sq->max_sge_num = cfg->max_sge;
	wqebb_depth = roundup_pow_of_two(sqe_bb_cnt * cfg->depth);
	if (cdma_u_alloc_queue_buf(sq, wqebb_depth, CDMA_JFS_WQEBB,
							   CDMA_HW_PAGE_SIZE, true)) {
		CDMA_LOG_ERR("alloc jfs wqe buf failed.\n");
		(void)pthread_spin_destroy(&sq->lock);
		return -EINVAL;
	}

	return 0;
}

static int cdma_verify_jfs_param(struct dma_context *ctx,
				 struct dma_jfs_cfg *cfg)
{
	struct cdma_device_cap *caps = &ctx->dma_dev->attr.dev_cap;

	if (!cfg->depth || cfg->depth > caps->max_jfs_depth ||
		cfg->max_sge > caps->max_jfs_sge) {
		CDMA_LOG_ERR("jfs param is invalid, depth = %u, sge = %u, \
					 max_depth = %u, max_jfs_sge = %u.\n",
					 cfg->depth, cfg->max_sge, caps->max_jfs_depth,
					 caps->max_jfs_sge);
		return -EINVAL;
	}

	return 0;
}

static inline void cdma_u_delete_sq(struct cdma_u_jetty_queue *sq)
{
	cdma_u_free_queue_buf(sq);
	pthread_spin_destroy(&sq->lock);
}

struct dma_jfs *cdma_u_create_jfs(struct dma_context *ctx,
				  struct dma_jfs_cfg *cfg)
{
	struct cdma_u_jfs *jfs;
	int ret;

	if (!ctx || !cfg || !ctx->dma_dev) {
		CDMA_LOG_ERR("create jfs parameter invalid.\n");
		return NULL;
	}

	ret = cdma_verify_jfs_param(ctx, cfg);
	if (ret)
		return NULL;

	jfs = (struct cdma_u_jfs *)calloc(1, sizeof(*jfs));
	if (!jfs) {
		CDMA_LOG_ERR("alloc jfs memory failed.\n");
		return NULL;
	}

	if (cdma_u_create_sq(&jfs->sq, cfg)) {
		CDMA_LOG_ERR("create sq failed.\n");
		goto err_create_sq;
	}

	jfs->jfs_type = CDMA_NORMAL_JETTY_TYPE;
	if (cdma_u_exec_create_jfs_cmd(ctx, jfs, cfg))
		goto err_exec_cmd;

	jfs->sq.db.id = jfs->base.jfs_id;
	jfs->sq.db.type = CDMA_MMAP_JETTY_DSQE;
	jfs->sq.idx = jfs->base.jfs_id;

	if (cdma_u_alloc_db(ctx, &jfs->sq.db))
		goto err_alloc_db;

	jfs->sq.dwqe_addr = (void *)jfs->sq.db.addr;

	return &jfs->base;

err_alloc_db:
	cdma_u_cmd_delete_jfs(&jfs->base);
err_exec_cmd:
	cdma_u_delete_sq(&jfs->sq);
err_create_sq:
	free(jfs);

	return NULL;
}

int cdma_u_delete_jfs(struct dma_jfs *jfs)
{
	struct cdma_u_context *cdma_ctx;
	struct cdma_u_jfs *cdma_jfs;
	int ret;

	if (!jfs || !jfs->dma_ctx) {
		CDMA_LOG_ERR("dma parameter invalid in delete jfs.\n");
		return -EINVAL;
	}

	cdma_ctx = to_cdma_u_ctx(jfs->dma_ctx);
	cdma_jfs = to_cdma_u_jfs(jfs);
	if (!cdma_ctx || !cdma_jfs) {
		CDMA_LOG_ERR("user dma parameter invalid in delete jfs.\n");
		return -EINVAL;
	}

	ret = cdma_u_cmd_delete_jfs(jfs);
	if (ret)
		CDMA_LOG_WARN("cdma delete jfs cmd failed.\n");

	if (!!jfs->jfs_cfg.jfc)
		cdma_u_clean_jfc((dma_jfc_t *)jfs->jfs_cfg.jfc, jfs->jfs_id);

	cdma_u_free_db(jfs->dma_ctx, &cdma_jfs->sq.db);
	cdma_u_delete_sq(&cdma_jfs->sq);
	free(cdma_jfs);

	return 0;
}

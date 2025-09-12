/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __CDMA_U_JFC_H__
#define __CDMA_U_JFC_H__

#include "cdma_u_common.h"

#define CDMA_U_MIN_JFC_DEPTH 64

struct cdma_u_jfc_cqe {
	/* DW0 */
	uint32_t s_r : 1;
	uint32_t is_jetty : 1;
	uint32_t owner : 1;
	uint32_t inline_en : 1;
	uint32_t opcode : 3;
	uint32_t fd : 1;
	uint32_t rsv : 8;
	uint32_t substatus : 8;
	uint32_t status : 8;
	/* DW1 */
	uint32_t entry_idx : 16;
	uint32_t local_num_l : 16;
	/* DW2 */
	uint32_t local_num_h : 4;
	uint32_t rmt_idx : 20;
	uint32_t rsv1 : 8;
	/* DW3 */
	uint32_t tpn : 24;
	uint32_t rsv2 : 8;
	/* DW4 */
	uint32_t byte_cnt;
	/* DW5 ~ DW6 */
	uint32_t user_data[2];
	/* DW7 ~ DW10 */
	uint32_t rmt_eid[4];
	/* DW11 ~ DW12 */
	uint32_t imm_data_l;
	uint32_t imm_data_h;
	/* DW13 ~ DW15 */
	uint32_t inline_data[3];
};

dma_jfce_t *cdma_u_create_jfce(struct dma_context *ctx);

dma_status cdma_u_delete_jfce(dma_jfce_t *jfce);

dma_jfc_t *cdma_u_create_jfc(struct dma_context *ctx, dma_jfc_cfg_t *cfg);

dma_status cdma_u_delete_jfc(dma_jfc_t *jfc);

dma_status cdma_u_rearm_jfc(dma_jfc_t *jfc, bool solicited_only);

void cdma_u_clean_jfc(dma_jfc_t *jfc, uint32_t jetty_id);

#endif

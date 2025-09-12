/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __CDMA_U_COMMON_H__
#define __CDMA_U_COMMON_H__

#include <unistd.h>
#include <stdatomic.h>
#include <arm_neon.h>
#include <stddef.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>
#include <sys/mman.h>
#include "cdma_u_types.h"

#define CDMA_JFC_DB_OFFSET 0

#define check_types_match(expr1, expr2)		\
	((typeof(expr1) *)0 != (typeof(expr2) *)0)

#ifndef container_of
#define container_off(containing_type, member)\
	offsetof(containing_type, member)
#define container_of(member_ptr, containing_type, member)	\
	((containing_type *)					\
	((void *)(member_ptr)					\
	- container_off(containing_type, member))		\
	+ (uint8_t)check_types_match(*(member_ptr), ((containing_type *)0)->member))
#endif


struct cdma_u_doorbell {
	uint32_t id;
	enum db_mmap_type type;
	void volatile *addr;
};

struct cdma_u_context {
	struct dma_context dma_ctx;
	void *db_addr;
	uint32_t page_size;
	struct cdma_u_db_page *page;
	pthread_mutex_t page_mutex;
	struct cdma_u_doorbell db;
	uint8_t cqe_size;
	uint8_t dwqe_enable;
	int async_fd;
};

static inline void cdma_mmap_set_command(uint32_t command, off_t *offset)
{
	uint32_t offset_u = (uint32_t)*offset;

	offset_u |= (command & (uint32_t)MAP_COMMAND_MASK);
	*offset = (off_t)offset_u;
}

static inline void cdma_mmap_set_index(unsigned long index, off_t *offset)
{
	unsigned long offset_u = (unsigned long)*offset;

	offset_u |= ((index & (unsigned long)MAP_INDEX_MASK) << MAP_INDEX_SHIFT);
	*offset = (off_t)offset_u;
}

static inline off_t get_mmap_offset(uint32_t idx, int page_size, uint32_t cmd)
{
	off_t offset = 0;

	cdma_mmap_set_command(cmd, &offset);
	cdma_mmap_set_index(idx, &offset);

	return offset * page_size;
}

static inline struct cdma_u_context *to_cdma_u_ctx(struct dma_context *ctx)
{
	return container_of(ctx, struct cdma_u_context, dma_ctx);
}

#endif

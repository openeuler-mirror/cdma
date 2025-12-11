# SPDX-License-Identifier: MIT
# Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.

cmake_minimum_required(VERSION 3.5)
project(CDMA_SO VERSION ${PROJECT_VERSION} LANGUAGES C CXX)

file(GLOB_RECURSE CDMA_SO_SRC *.c)

add_library(CDMA_SO SHARED ${CDMA_SO_SRC})

set(CDMA_USER_EXT_DIR include/)
set(CDMA_USER_KERNEL_DIR kernel_headers/)

target_include_directories(CDMA_SO PUBLIC
	${CDMA_USER_EXT_DIR}
	${CDMA_USER_KERNEL_DIR})

target_link_libraries(CDMA_SO PUBLIC ummu)
set_target_properties(CDMA_SO PROPERTIES OUTPUT_NAME cdma SOVERSION ${LIB_SOVERSION} VERSION ${PROJECT_VERSION})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -fno-common -std=gnu99 -Wuninitialized -Wno-error=format -Wundef -Wunused -Wdate-time -Wfloat-equal -Wshadow -Wvla \
        -Wdisabled-optimization -Wempty-body -Wignored-qualifiers -Wimplicit-fallthrough=3 -Wtype-limits -Wshift-negative-value -Wswitch-default \
        -Wframe-larger-than=8192 -Wshift-overflow=2 -Wwrite-strings -Wmissing-format-attribute -Wformat-nonliteral -Wduplicated-cond -Wtrampolines \
        -Wlogical-op -Wsuggest-attribute=format -Wduplicated-branches -Wmissing-include-dirs -Wformat-signedness -Wmissing-declarations \
        -Wreturn-local-addr -Wredundant-decls -Wfloat-conversion -Wmissing-prototypes -Wstrict-prototypes")

install(TARGETS CDMA_SO LIBRARY DESTINATION lib64 OPTIONAL)
install(FILES include/cdma_u_lib.h DESTINATION include/)
install(FILES kernel_headers/cdma_abi.h DESTINATION include/)


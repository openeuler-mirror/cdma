# SPDX-License-Identifier: MIT
# Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.

project(libcdma)
cmake_minimum_required(VERSION 3.22)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wl,-rpath-link,${CMAKE_RPATH}")

file(GLOB_RECURSE CDMA_SO_SRC *.c)

add_library(cdma_so SHARED ${CDMA_SO_SRC})

set(CDMA_USER_EXT_DIR include/)
set(CDMA_USER_KERNEL_DIR kernel_headers/)

target_include_directories(cdma_so PUBLIC
	${CDMA_USER_EXT_DIR}
	${CDMA_USER_KERNEL_DIR})

target_link_libraries(cdma_so PUBLIC ummu)
set_target_properties(cdma_so PROPERTIES OUTPUT_NAME cdma)

if(GCOV)
        set(CMAKE_C_FLAGS "-Wall -Wextra -Wfloat-equal -fno-common -std=gnu99 -fprofile-arcs -ftest-coverage")
        set(CMAKE_LD_FLAGS "-s -lgcov")
else()
        set(CMAKE_C_FLAGS "-Wall -Wextra -Wfloat-equal -fno-common -std=gnu99")
        set(CMAKE_LD_FLAGS "-s")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wuninitialized -Wno-error=format -Wundef -Wunused -Wdate-time -Wfloat-equal -Wshadow -Wvla \
        -Wdisabled-optimization -Wempty-body -Wignored-qualifiers -Wimplicit-fallthrough=3 -Wtype-limits -Wshift-negative-value -Wswitch-default \
        -Wframe-larger-than=8192 -Wshift-overflow=2 -Wwrite-strings -Wmissing-format-attribute -Wformat-nonliteral -Wduplicated-cond -Wtrampolines \
        -Wlogical-op -Wsuggest-attribute=format -Wduplicated-branches -Wmissing-include-dirs -Wformat-signedness -Wmissing-declarations \
        -Wreturn-local-addr -Wredundant-decls -Wfloat-conversion -Wmissing-prototypes -Wstrict-prototypes")

install(TARGETS cdma_so LIBRARY DESTINATION lib64 OPTIONAL)
install(FILES include/cdma_u_lib.h
	DESTINATION include/)

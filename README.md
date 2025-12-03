# CDMA
## Overview
CDMA library provides CDMA (Crystal Direct Memory Access) functionality for
user-space applications, enabling asynchronous memory read and write operations
between hosts or between host and devices.

The key features are described as follows:

1. Peer-to-peer communication between hosts, enabling bidirectional asynchronous memory read or write.
2. Asynchronous memory read and write between host and devices via DMA.
3. Asynchronous memory read and write between devices and host via DMA.

## Directory Structure
    ├── cdma/
    |   ├── doc/               // cdma api doc files
    │   ├── include/           // cdma header files
    │   ├── kernel_include/    // cdma abi files
    └── ...                    // cdma function implementation files

## Header Files
[cdma_u_lib.h](./include/cdma_u_lib.h)

## Note
Please refer to the CDMA library [API Doc](./doc/CDMA_API.md) for development.

## Support
If there is any issue or question, please email the specific information related
to the issue or question to <dev@openeuler.org> or vendor's support channel.

## License
SPDX-License-Identifier: MIT

## Copyright
Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.

THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
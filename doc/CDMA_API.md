# NAME

CDMA : Crystal Direct Memory Access

# DESCRIPTION

CDMA library provides CDMA (Crystal Direct Memory Access) functionality for
user-space applications, enabling asynchronous memory read and write operations
between hosts or between host and devices.

The key features are described as follows:

1. Peer-to-peer communication between hosts, enabling bidirectional asynchronous memory read or write.

2. Asynchronous memory read and write between host and devices via DMA.

3. Asynchronous memory read and write between devices and host via DMA.

# FUNCTIONS

##  DMA Device Interface

###  dma_get_device_list

```
   Prototype
      struct dma_device *dma_get_device_list(uint32_t *num_devices)
   Description
      Get the DMA device list.
   Parameters
      @num_devices: DMA device number
   Return
      Address of the first device in the list
   Explain
      Users can perform subsequent resource creation operations using a pointer
      to a DMA device in the list.
```

###  dma_get_device_by_eid

```
   Prototype
      struct dma_device *dma_get_device_by_eid(struct dev_eid *eid)
   Description
      Obtain the device handle based on the device EID.
   Parameters
      @eid: device eid pointer
   Return
      DMA device structure pointer
   Explain
      Choose one to use with the dma_get_device_list function.
```

###  dma_free_device_list

```
   Prototype
      void dma_free_device_list(struct dma_device *dev_list, uint32_t num_devices)
   Description
      Release the DMA device list.
   Parameters
      @dev_list: DMA device list
      @num_devices: DMA device number
   Return
      NA
   Explain
      It can be called after using dev_list and must be called.
```

##  DMA Context Interface

###  dma_create_context

```
   Prototype
      struct dma_context *dma_create_context(struct dma_device *dma_dev)
   Description
      Create DMA User Context.
   Parameters
      @dma_dev: DMA device pointer
   Return
      DMA context structure pointer
   Explain
      The context is used to store resources such as Queue and Segment, and
      returns a pointer to the context information.
```

###  dma_delete_context

```
   Prototype
      void dma_delete_context(struct dma_context *ctx)
   Description
      Delete DMA User Context.
   Parameters
      @ctx: DMA context pointer
   Return
      NA
   Explain
      NA
```

##  DMA Queue Interface

###  dma_alloc_queue

```
   Prototype
      struct dma_queue *dma_alloc_queue(struct dma_context *ctx, struct queue_cfg *cfg)
   Description
      Create a DMA queue for operations such as DMA read and write.
   Parameters
      @dma_dev: DMA device pointer
   Return
      DMA context structure pointer
   Explain
      The user uses the queue for DMA read and write operations.
```

###  dma_free_queue

```
   Prototype
      void dma_free_queue(struct dma_queue *queue)
   Description
      Free the DMA queue.
   Parameters
      @queue: the DMA queue pointer
   Return
      NA
   Explain
      NA
```

##  Segment Management Interface

###  dma_register_seg

```
   Prototype
      struct dma_seg *dma_register_seg(struct dma_context *ctx, struct dma_seg_cfg *cfg)
   Description
      Register local Segment information.
   Parameters
      @ctx: DMA context pointer
      @cfg: DMA segment configuration information pointer
   Return
      DMA segment structure pointer
   Explain
      The Segment stores local Payload information for operations such as DMA
      read and write, and returns a pointer to the Segment information.
```

###  dma_unregister_seg

```
   Prototype
      void dma_unregister_seg(struct dma_context *ctx, struct dma_seg *seg)
   Description
      Unregister local Segment information.
   Parameters
      @ctx: DMA context pointer
      @seg: DMA segment pointer
   Return
      NA
   Explain
      NA
```

###  dma_import_seg

```
   Prototype
      struct dma_seg *dma_import_seg(struct dma_seg_cfg *cfg)
   Description
      Import remote Segment information.
   Parameters
      @cfg: DMA segment configuration information pointer
   Return
      DMA segment structure pointer
   Explain
      The Segment stores the remote Payload information for operations such as
      DMA read and write, and returns the Segment information pointer.
```

###  dma_unimport_seg

```
   Prototype
      void dma_unimport_seg(struct dma_seg *seg)
   Description
      Unimport remote Segment information.
   Parameters
      @seg: DMA segment pointer
   Return
      NA
   Explain
      NA
```

##  DMA Command Interface

###  dma_write

```
   Prototype
      dma_status dma_write(struct dma_queue *queue, struct dma_seg *rmt_seg,
         struct dma_seg *local_seg)
   Description
      DMA write operation request.
   Parameters
      @queue: DMA queue pointer
      @rmt_seg: the remote segment pointer
      @local_seg: the local segment pointer
   Return
      Operation result, DMA_STATUS_OK on success
   Explain
      Invoke this interface to initiate a unilateral write operation request,
      sending the specified number of bytes of data from the designated local
      memory starting position to the specified destination address.
      Once the data is successfully written to the remote node, the application
      can poll the queue to obtain the completion message.
```

###  dma_read

```
   Prototype
      dma_status dma_read(struct dma_queue *queue, struct dma_seg *rmt_seg,
         struct dma_seg *local_seg)
   Description
      DMA read operation request.
   Parameters
      @queue: DMA queue pointer
      @rmt_seg: the remote segment pointer
      @local_seg: the local segment pointer
   Return
      Operation result, DMA_STATUS_OK on success
   Explain
      Invoke this interface to initiate a unidirectional read operation request,
      reading data from the specified remote address to the designated local
      cache starting position.
      Once the data is successfully read from the remote node to the local memory,
      the application can poll the queue to obtain the completion message.
```

###  dma_write_with_notify

```
   Prototype
      dma_status dma_write_with_notify(struct dma_queue *queue,
         struct dma_seg *rmt_seg, struct dma_seg *local_seg, struct dma_seg *notify_seg,
         uint64_t notify_data)
   Description
      DMA write with notify operation request.
   Parameters
      @queue: DMA queue pointer
      @rmt_seg: the remote segment pointer
      @local_seg: the local segment pointer
      @notify_seg: the segment pointer for notify
      @notify_data: data value used for notify
   Return
      Operation result, DMA_STATUS_OK on success
   Explain
      Invoke this interface to initiate a Write notify operation request for a
      unilateral operation, which sends a specified number of bytes of data from
      a designated starting position in local memory to a specified destination
      address.
      Once the data is successfully written to the remote node, the application
      can poll the queue to obtain the completion message.
```

###  dma_cas

```
   Prototype
      dma_status dma_cas(struct dma_queue *queue, struct dma_seg *rmt_seg,
         struct dma_seg *local_seg, uint64_t cmp, uint64_t swap)
   Description
      DMA CAS operation request.
   Parameters
      @queue: DMA queue pointer
      @rmt_seg: the remote segment pointer
      @local_seg: the local segment pointer
      @cmp: compare data, length <= 8B: CMP value, length > 8B: data address.
      @swap: swap data, length <= 8B: swap value, length > 8B: data address.
   Return
      Operation result, DMA_STATUS_OK on success
   Explain
      Initiate a request for a unilateral atomic CAS operation. Once the operation
      is successful, the application can poll the queue to obtain the completion
      message.
```

###  dma_faa

```
   Prototype
      dma_status dma_faa(struct dma_queue *queue, struct dma_seg *rmt_seg,
         struct dma_seg *local_seg, uint64_t add)
   Description
      DMA FAA operation request.
   Parameters
      @queue: DMA queue pointer
      @rmt_seg: the remote segment pointer
      @local_seg: the local segment pointer
      @add: add data for faa operation
   Return
      Operation result, DMA_STATUS_OK on success
   Explain
      Initiate a request for a unilateral atomic FAA operation. Once the operation
      is successful, the application can poll the queue to obtain the completion
      message.
```

##  DMA Event Interface

###  dma_poll_queue

```
   Prototype
      int dma_poll_queue(struct dma_queue *queue, uint32_t cr_cnt, struct dma_cr *cr)
   Description
      DMA polling queue.
   Parameters
      @queue: DMA queue pointer
      @cr_cnt: number of completion record
      @cr: completion record pointe
   Return
      Polling operation results  >0 on success, others on failed
   Explain
      Poll the DMA channel completion event, and the polling result is returned
      to the address specified by the parameter cr. The cr data structure includes
      information such as the result of the request execution, the length of data
      transferred, and the type of error.
      The caller must ensure that the number of parameters cr_cnt matches the
      number of addresses specified by cr.
```

###  dma_wait_queue

```
   Prototype
      int dma_wait_queue(struct dma_queue *queue, uint32_t cr_cnt, int timeout,
         struct dma_cr *cr)
   Description
      Wait for completion event.
   Parameters
      @queue: DMA queue pointer
      @cr_cnt: number of completion record
      @timeout: timeout time for waiting
      @cr: completion record pointer
   Return
      Operation result, 0 on 0 event success, 1 on 1 event success, others on failed
   Explain
      Wait for a Queue to generate a new JFCE, which blocks the calling process.
```

###  dma_wait_ae

```
   Prototype
      int dma_wait_ae(struct dma_context *ctx, struct dma_aeqe *aeqe)
   Description
      Wait for asynchronous events.
   Parameters
      @ctx: DMA context pointer
      @aeqe: asynchronous event queue entity pointer
   Return
      Operation result, 0 on 0 event success, 1 on 1 event success, others on failed
   Explain
      User query related to device or JETTY asynchronous events.

```
# EXAMPLES

##  LIB Usage

libcdma.so interface API usage:

```
   #include "cdma_u_lib.h"

   typedef struct dma_device * (*fun_dma_get_device_list)(uint32_t *);

   void dma_get_device_list_sample()
   {
      struct dma_device *dev_list;
      uint32_t dev_num = 0;

      void *handle = dlopen("libcdma.so", RTLD_GLOBAL | RTLD_NOW);
      ...
      fun_dma_get_device_list dma_get_device_list = dlsym(handle, "dma_get_device_list");
      ...
      dev_list = dma_get_device_list(&dev_num);
      ...
   }

```

##  API Usage

```
   #define POLL_LOOP_EXAMP 100
   #define POLL_USLEEP_EXAMP 1000
   #define QUEUE_DEPTH_EXAMP 512
   #define QUEUE_RMT_EID_EXAMP 2
   #define QUEUE_DCAN_EXAMP 1

   struct dma_seg_cfg local_seg_cfg = {};
   struct dma_seg_cfg rmt_seg_cfg = {};
   struct dma_seg *local_seg, *rmt_seg;
   struct queue_cfg queue_cfg = {};
   uint32_t loop = POLL_LOOP_EXAMP;
   struct dma_context *dma_ctx;
   struct dma_device *dev_list;
   struct dma_queue *dma_queue;
   struct dma_device *dma_dev;
   struct dma_cr ret_cr = {};
   uint32_t dev_num = 0;
   dma_status status;
   int ret = -EINVAL;

   dev_list = dma_get_device_list(&dev_num);
   if (!dev_list || !dev_num) {
      printf("get device list failed\n");
      return;
   }
   dma_dev = &dev_list[0];

   dma_ctx = dma_create_context(dma_dev);
   if (!dma_ctx) {
      printf("create context failed.\n");
      goto free_dev_list;
   }

   queue_cfg.queue_depth = QUEUE_DEPTH_EXAMP;
   queue_cfg.rmt_eid.dw0 = QUEUE_RMT_EID_EXAMP;
   queue_cfg.dcna = QUEUE_DCAN_EXAMP;
   dma_queue = dma_alloc_queue(dma_ctx, &cfg);
   if (!dma_queue) {
      printf("allocate queue failed.\n");
      goto delete_ctx;
   }

   local_seg_cfg.addr = (uint64_t)local_buf_addr; // Input parameter, local payload address
   local_seg_cfg.len = local_buf_len; // Input parameter, local payload memory length

   local_seg = dma_register_seg(dma_ctx, &local_seg_cfg);
   if (!local_seg) {
      printf("register local segment failed.\n");
      goto free_queue;
   }

   rmt_seg_cfg.addr = (uint64_t)rmt_buf_addr; // Input parameter, remote payload address
   rmt_seg_cfg.len = rmt_buf_len; // Input parameter, remote payload memory length

   rmt_seg = dma_import_seg(&rmt_seg_cfg);
   if (!rmt_seg) {
      printf("import rmt segment failed.\n");
      goto unregister_seg;
   }

   status = dma_write(dma_queue, rmt_seg, local_seg);
   if (status != DMA_STATUS_OK) {
      printf("write failed, status = %d.\n", status);
      goto unimport_seg;
   }

   while (loop > 0) {
      ret = dma_poll_queue(dma_queue, 1, &ret_cr);
      if (ret == 1)
         break;
      usleep(POLL_USLEEP_EXAMP);
      loop --;
   }
   ...

   unimport_seg:
      dma_unimport_seg(rmt_seg);
   unregister_seg:
      dma_unregister_seg(dma_ctx, local_seg);
   free_queue:
      dma_free_queue(dma_queue);
   delete_ctx:
      dma_delete_context(dma_ctx);
   free_dev_list:
      dma_free_device_list(dev_list, dev_num);
   ...
```

# SUPPORT
If there is any issue or question, please email the specific information related
to the issue or question to <dev@openeuler.org> or vendor's support channel.

# LICENSE
SPDX-License-Identifier: MIT

# COPYRIGHT

Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.

THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
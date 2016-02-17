#Prefetcher
Cache prefetcher for TDT4260

> The prefetcher must implement the three functions *prefetch_init*,
> *prefetch_access* and *prefetch_complete*. The implementation may be empty.

> The function *prefetch_init(void)* is called at the start of the simulation
> to allow the prefetcher to initialize any data structures it will need.
> When the L2 cache is accessed by the CPU (through the L1 cache), the function
> *void prefetch_access(AccessStat stat)* is called with an argument
> (AccessStat stat) that gives various information about the access.

> When the prefetcher decides to issue a prefetch request, it should call
> issue *prefetch(Addr addr)*, which queues up a prefetch request for the
> block containing addr.

> When a cache block that was requested by issue prefetch arrives from
> memory, prefetch complete is called with the address of the completed
> request as parameter.

> Prefetches issued by *issue_prefetch(Addr addr)* go into a prefetch request
> queue. The cache will issue requests from the queue when it is not fetching
> data for the CPU. This queue has a fixed size (available as MAX QUEUE SIZE),
> and when it gets full, the oldest entry is evicted. If you want to check the
> current size of this queue, use the function *current_queue_size(void).


#### Interface #defines

| Constants         | Value    | Description                                 |
| ----------------- |:--------:| ------------------------------------------- |
| BLOCK_SIZE        | 64       | Size of cache blocks (cache lines) in bytes |
| MAX_QUEUE_SIZE    | 100      | Maximum number of pending prefetch requests |
| MAX_PHYS_MEM_SIZE | 2^28 - 1 | The largest possible physical memory address|

####Functions callable from the user-defined prefetcher

| Function                                             | Description                                     |
| ---------------------------------------------------- | ----------------------------------------------- |
| void&#160;__issue_prefetch__(Addr&#160;addr)         | Called by the prefetcher to initiate a prefetch |
| int&#160;__get_prefetch_bit__(Addr&#160;addr)        | Is the prefetch bit set for addr?               |
| int&#160;__set_prefetch_bit__(Addr&#160;addr)        | Set the prefetch bit for addr                   |
| int&#160;__clear_prefetch_bit__(Addr&#160;addr)      | Clear the prefetch bit for addr                 |
| int&#160;__in_cache__(Addr&#160;addr)                | Is addr currently in the L2 cache?              |
| int&#160;__in_mshr_queue__(Addr&#160;addr)           | Is there a prefetch request for addr in the MSHR (miss status holding register) queue? |
| int&#160;__current_queue_size__(void)                | Returns the number of queued prefetch requests  |
| void&#160;__DPRINTF__(trace,&#160;format,&#160;...)  | Macro to print debug information. trace is a trace flag (HWPrefetch), and format is a printf format string. |

####AccessStat members

| Variable      | Description                                                             |
| ------------- | ----------------------------------------------------------------------- |
| Addr pc       | The address of the instruction that caused the access (Program Counter) |
| Addr mem addr | The memory address that was requested                                   |
| Tick time     | The simulator time cycle when the request was sent                      |
| int miss      | Whether this demand access was a cache hit or miss                      |

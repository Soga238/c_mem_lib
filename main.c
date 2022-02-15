#include "stdio.h"
#include "time.h"
#include "windows.h"

#include "3rdparty/TencentOS/tos_mmheap.h"
#include "3rdparty/FreeRTOS/heap_4.h"
#include "3rdparty/ThreadX/tx_api.h"

TX_BYTE_POOL  pool;
k_mmheap_ctl_t       k_mmheap_ctl;

void do_test(void *(*fn_malloc)(size_t size), void(*fn_free)(void *p))
{
#define MSECOND 1000000

    char *ptr;
    float timeuse;
    struct timeval tpstart, tpend;
    size_t size, i, loops = 1000000, no = 0;

    srand((int) time(0));
    mingw_gettimeofday(&tpstart, NULL);

    for (i = 0, size = (size_t)rand() & 0x0000f; i < loops; ++i) {
        if (size > 0) {
            ptr = fn_malloc(size);
            if (NULL == ptr) {
                printf("malloc %d failed\r\n", size);
                return;
            }

            /*! 偶数次，释放内存 */
            fn_free(ptr);
            no += size;
        }
    }

    mingw_gettimeofday(&tpend, NULL);

    timeuse = MSECOND * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec
        - tpstart.tv_usec;
    timeuse /= MSECOND;

    printf("Used Time [%f] with [%llu] loops, no free %llu\n", timeuse, loops, no);

#undef MSECOND
}

void *tx_malloc(size_t size)
{
    void * MallocAddr = NULL;
    tx_byte_allocate(&pool, (void **)&MallocAddr, size, 0);
    return MallocAddr;
}

void tx_free(void *ptr)
{
    tx_byte_release(ptr);
}

int main(void)
{
#define BUFFER_SIZE configTOTAL_HEAP_SIZE

    char buffer[BUFFER_SIZE];

    do_test(malloc, free);

    do_test(pvPortMalloc, vPortFree);

    mmheap_init();
    mmheap_init_with_pool(buffer, sizeof(buffer));
    do_test(tos_mmheap_alloc, tos_mmheap_free);

    tx_byte_pool_create(&pool, "name", buffer, BUFFER_SIZE);
    do_test(tx_malloc, tx_free);

    return 0;
}
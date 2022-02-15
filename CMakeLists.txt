cmake_minimum_required(VERSION 3.21)
project(c_mem_lib C)

set(CMAKE_C_STANDARD 99)

add_executable(c_mem_lib main.c
        3rdparty/TencentOS/tos_mmheap.c
        3rdparty/TencentOS/tos_mmheap.h
        3rdparty/TencentOS/_required.h
        3rdparty/FreeRTOS/heap_4.c
        3rdparty/FreeRTOS/heap_4.h

        3rdparty/ThreadX/tx_api.h
        3rdparty/ThreadX/tx_byte_pool.h
        3rdparty/ThreadX/tx_byte_allocate.c
        3rdparty/ThreadX/tx_byte_pool_search.c
        3rdparty/ThreadX/tx_byte_pool_create.c
        3rdparty/ThreadX/tx_byte_release.c
        )

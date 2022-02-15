/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** ThreadX Component                                                     */
/**                                                                       */
/**   Application Interface (API)                                         */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/**************************************************************************/
/*                                                                        */
/*  APPLICATION INTERFACE DEFINITION                       RELEASE        */
/*                                                                        */
/*    tx_api.h                                            PORTABLE C      */
/*                                                           6.1.9        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    William E. Lamie, Microsoft Corporation                             */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This file defines the basic Application Interface (API) to the      */
/*    high-performance ThreadX real-time kernel.  All service prototypes  */
/*    and data structure definitions are defined in this file.            */
/*    Please note that basic data type definitions and other architecture-*/
/*    specific information is contained in the file tx_port.h.            */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020      William E. Lamie        Initial Version 6.0           */
/*  09-30-2020      William E. Lamie        Modified comment(s), and      */
/*                                            updated product constants,  */
/*                                            added new thread execution  */
/*                                            state TX_PRIORITY_CHANGE,   */
/*                                            added macros for casting    */
/*                                            pointers to ALIGN_TYPE,     */
/*                                            resulting in version 6.1    */
/*  10-16-2020      William E. Lamie        Modified comment(s), and      */
/*                                            increased patch version,    */
/*                                            resulting in version 6.1.1  */
/*  11-09-2020      Yuxin Zhou              Modified comment(s), and      */
/*                                            moved TX_THREAD_GET_SYSTEM_ */
/*                                            STATE to tx_api.h,          */
/*                                            resulting in version 6.1.2  */
/*  12-31-2020      William E. Lamie        Modified comment(s), and      */
/*                                            increased patch version,    */
/*                                            resulting in version 6.1.3  */
/*  03-02-2021      Scott Larson            Modified comment(s), and      */
/*                                            order defines numerically,  */
/*                                            add option to remove FileX  */
/*                                            pointer,                    */
/*                                            resulting in version 6.1.5  */
/*  04-02-2021      Scott Larson            Modified comment(s), and      */
/*                                            update patch number,        */
/*                                            resulting in version 6.1.6  */
/*  06-02-2021      Yuxin Zhou              Modified comment(s), added    */
/*                                            Execution Profile support,  */
/*                                            resulting in version 6.1.7  */
/*  08-02-2021      Scott Larson            Modified comment(s), and      */
/*                                            update patch number,        */
/*                                            resulting in version 6.1.8  */
/*  10-15-2021      Yuxin Zhou              Modified comment(s),          */
/*                                            update patch number,        */
/*                                            resulting in version 6.1.9  */
/*                                                                        */
/**************************************************************************/

#ifndef TX_API_H
#define TX_API_H


/* Determine if a C++ compiler is being used.  If so, ensure that standard
   C is used to process the API information.  */

#ifdef __cplusplus

/* Yes, C++ compiler is present.  Use standard C.  */
extern   "C" {

#endif


/* Include the port-specific data type file.  */

#include "tx_port.h"


/* Define basic constants for the ThreadX kernel.  */
/* API input parameters and general constants.  */

#define TX_TRUE                         ((UINT)   1)
#define TX_FALSE                        ((UINT)   0)
#define TX_NULL                         ((void *) 0)
//#define TX_EMPTY                        ((ULONG)  0)

/* API return values.  */

#define TX_SUCCESS                      ((UINT) 0x00)
#define TX_PTR_ERROR                    ((UINT) 0x03)
#define TX_NO_MEMORY                    ((UINT) 0x10)

#define TX_MEMSET(a,b,c)                                memset((a),(b),(c))

#define TX_UCHAR_POINTER_ADD(a,b)                       (((UCHAR *) (a)) + ((UINT) (b)))
#define TX_UCHAR_POINTER_SUB(a,b)                       (((UCHAR *) (a)) - ((UINT) (b)))
#define TX_UCHAR_POINTER_DIF(a,b)                       ((ULONG)(((UCHAR *) (a)) - ((UCHAR *) (b))))

#define TX_UCHAR_TO_INDIRECT_BYTE_POOL_POINTER(a)       ((TX_BYTE_POOL **) ((VOID *) (a)))
#define TX_VOID_TO_UCHAR_POINTER_CONVERT(a)             ((UCHAR *) ((VOID *) (a)))
#define TX_UCHAR_TO_ALIGN_TYPE_POINTER_CONVERT(a)       ((ALIGN_TYPE *) ((VOID *) (a)))
#define TX_UCHAR_TO_INDIRECT_UCHAR_POINTER_CONVERT(a)   ((UCHAR **) ((VOID *) (a)))
#define TX_BYTE_POOL_TO_UCHAR_POINTER_CONVERT(a)        ((UCHAR *) ((VOID *) (a)))

/* Define basic alignment type used in block and byte pool operations. This data type must
   be at least 32-bits in size and also be large enough to hold a pointer type.  */

#ifndef ALIGN_TYPE_DEFINED
/* TODO: Backup the end of the pool pointer and build the pre-allocated block.
                内存池最后一块，最后 X(sizeof(ALIGN_TYPE)) 字节存储 TX_BYTE_BLOCK_ALLOC */
//#define ALIGN_TYPE      ULONG
#define ALIGN_TYPE      unsigned long long
#endif

/* Define the byte memory pool structure utilized by the application.  */

typedef struct TX_BYTE_POOL_STRUCT
{
    /* Define the number of available bytes in the pool.  */
    ULONG               tx_byte_pool_available;

    /* Define the number of fragments in the pool.  */
    UINT                tx_byte_pool_fragments;

    /* Define the head pointer of byte pool.  */
    UCHAR               *tx_byte_pool_list;

    /* Define the search pointer used for initial searching for memory
       in a byte pool.  */
    UCHAR               *tx_byte_pool_search;

    /* Save the start address of the byte pool's memory area.  */
    UCHAR               *tx_byte_pool_start;

    /* Save the byte pool's size in bytes.  */
    ULONG               tx_byte_pool_size;
} TX_BYTE_POOL;

UINT        _tx_byte_allocate(TX_BYTE_POOL *pool_ptr, VOID **memory_ptr, ULONG memory_size,
                              ULONG wait_option);
UINT        _tx_byte_pool_create(TX_BYTE_POOL *pool_ptr, CHAR *name_ptr, VOID *pool_start,
                                 ULONG pool_size);
UINT        _tx_byte_release(VOID *memory_ptr);

#define tx_byte_allocate                            _tx_byte_allocate
#define tx_byte_pool_create                         _tx_byte_pool_create
#define tx_byte_release                             _tx_byte_release

/* Determine if a C++ compiler is being used.  If so, complete the standard
   C conditional started above.  */
#ifdef __cplusplus
        }
#endif

#endif


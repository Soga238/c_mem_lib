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
/**   Byte Memory                                                         */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/**************************************************************************/
/*                                                                        */
/*  COMPONENT DEFINITION                                   RELEASE        */
/*                                                                        */
/*    tx_byte_pool.h                                      PORTABLE C      */
/*                                                           6.1          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    William E. Lamie, Microsoft Corporation                             */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This file defines the ThreadX byte memory management component,     */
/*    including all data types and external references.  It is assumed    */
/*    that tx_api.h and tx_port.h have already been included.             */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     William E. Lamie         Initial Version 6.0           */
/*  09-30-2020     Yuxin Zhou               Modified comment(s),          */
/*                                            resulting in version 6.1    */
/*                                                                        */
/**************************************************************************/

#ifndef TX_BYTE_POOL_H
#define TX_BYTE_POOL_H

/* Define byte memory control specific data definitions.  */
#ifndef TX_BYTE_BLOCK_FREE
#define TX_BYTE_BLOCK_FREE                      ((ULONG) 0xFFFFEEEEUL)
#endif

#ifndef TX_BYTE_BLOCK_MIN
#define TX_BYTE_BLOCK_MIN                       ((ULONG) 20)
#endif

#ifndef TX_BYTE_POOL_MIN
#define TX_BYTE_POOL_MIN                        ((ULONG) 100)
#endif

/* Define internal byte memory pool management function prototypes.  */

UCHAR       *_tx_byte_pool_search(TX_BYTE_POOL *pool_ptr, ULONG memory_size);


#endif

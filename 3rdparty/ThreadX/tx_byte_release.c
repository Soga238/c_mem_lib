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
/* Include necessary system files.  */

#include "tx_api.h"
#include "tx_byte_pool.h"


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _tx_byte_release                                    PORTABLE C      */
/*                                                           6.1          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    William E. Lamie, Microsoft Corporation                             */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function returns previously allocated memory to its            */
/*    associated memory byte pool.                                        */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    memory_ptr                        Pointer to allocated memory       */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    [TX_PTR_ERROR | TX_SUCCESS]       Completion status                 */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _tx_thread_system_preempt_check   Check for preemption              */
/*    _tx_thread_system_resume          Resume thread service             */
/*    _tx_thread_system_ni_resume       Non-interruptable resume thread   */
/*    _tx_byte_pool_search              Search the byte pool for memory   */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Application Code                                                    */
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
UINT  _tx_byte_release(VOID *memory_ptr)
{

UINT                status;
TX_BYTE_POOL        *pool_ptr;
UCHAR               *work_ptr;
UCHAR               *temp_ptr;
UCHAR               *next_block_ptr;
ALIGN_TYPE          *free_ptr;
TX_BYTE_POOL        **byte_pool_ptr;
UCHAR               **block_link_ptr;


    /* Default to successful status.  */
    status =  TX_SUCCESS;

    /* Set the pool pointer to NULL.  */
    pool_ptr =  TX_NULL;

    /* Lockout interrupts.  */
//    TX_DISABLE

    /* Determine if the memory pointer is valid.  */
    work_ptr =  TX_VOID_TO_UCHAR_POINTER_CONVERT(memory_ptr);
    if (work_ptr != TX_NULL)
    {

        /* Back off the memory pointer to pickup its header.  */
        work_ptr =  TX_UCHAR_POINTER_SUB(work_ptr, ((sizeof(UCHAR *)) + (sizeof(ALIGN_TYPE))));

        /* There is a pointer, pickup the pool pointer address.  */
        temp_ptr =  TX_UCHAR_POINTER_ADD(work_ptr, (sizeof(UCHAR *)));
        free_ptr =  TX_UCHAR_TO_ALIGN_TYPE_POINTER_CONVERT(temp_ptr);
        if ((*free_ptr) != TX_BYTE_BLOCK_FREE)
        {

            /* Pickup the pool pointer.  */
            temp_ptr =  TX_UCHAR_POINTER_ADD(work_ptr, (sizeof(UCHAR *)));
            byte_pool_ptr =  TX_UCHAR_TO_INDIRECT_BYTE_POOL_POINTER(temp_ptr);
            pool_ptr =  *byte_pool_ptr;

            /* See if we have a valid pool pointer.  */
            if (pool_ptr == TX_NULL)
            {

                /* Return pointer error.  */
                status =  TX_PTR_ERROR;
            }
        }
        else
        {

            /* Return pointer error.  */
            status =  TX_PTR_ERROR;
        }
    }
    else
    {

        /* Return pointer error.  */
        status =  TX_PTR_ERROR;
    }

    /* Determine if the pointer is valid.  */
    if (pool_ptr == TX_NULL)
    {

        /* Restore interrupts.  */
//        TX_RESTORE
    }
    else
    {
        /* Release the memory.  */
        temp_ptr =   TX_UCHAR_POINTER_ADD(work_ptr, (sizeof(UCHAR *)));
        free_ptr =   TX_UCHAR_TO_ALIGN_TYPE_POINTER_CONVERT(temp_ptr);
        *free_ptr =  TX_BYTE_BLOCK_FREE;

        /* Update the number of available bytes in the pool.  */
        block_link_ptr =  TX_UCHAR_TO_INDIRECT_UCHAR_POINTER_CONVERT(work_ptr);
        next_block_ptr =  *block_link_ptr;
        pool_ptr -> tx_byte_pool_available =
            pool_ptr -> tx_byte_pool_available + TX_UCHAR_POINTER_DIF(next_block_ptr, work_ptr);

        /* Determine if the free block is prior to current search pointer.  */
        if (work_ptr < (pool_ptr -> tx_byte_pool_search))
        {

            /* Yes, update the search pointer to the released block.  */
            pool_ptr -> tx_byte_pool_search =  work_ptr;
        }

//        TX_RESTORE
    }

    /* Return completion status.  */
    return(status);
}


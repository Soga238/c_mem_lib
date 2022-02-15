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
/*    _tx_byte_allocate                                   PORTABLE C      */
/*                                                           6.1          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    William E. Lamie, Microsoft Corporation                             */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function allocates bytes from the specified memory byte        */
/*    pool.                                                               */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    pool_ptr                          Pointer to pool control block     */
/*    memory_ptr                        Pointer to place allocated bytes  */
/*                                        pointer                         */
/*    memory_size                       Number of bytes to allocate       */
/*    wait_option                       Suspension option                 */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                            Completion status                 */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _tx_thread_system_suspend         Suspend thread service            */
/*    _tx_thread_system_ni_suspend      Non-interruptable suspend thread  */
/*    _tx_byte_pool_search              Search byte pool for memory       */
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
UINT  _tx_byte_allocate(TX_BYTE_POOL *pool_ptr, VOID **memory_ptr, ULONG memory_size,  ULONG wait_option)
{
UINT                        status;
UCHAR                       *work_ptr;
UINT                        suspended_count;
UINT                        finished;

    /* Round the memory size up to the next size that is evenly divisible by
       an ALIGN_TYPE (this is typically a 32-bit ULONG).  This guarantees proper alignment.  */
    memory_size = (((memory_size + (sizeof(ALIGN_TYPE)))-((ALIGN_TYPE) 1))/(sizeof(ALIGN_TYPE))) * (sizeof(ALIGN_TYPE));

    /* Disable interrupts.  */
//    TX_DISABLE

    /* Set the search finished flag to false.  */
    finished =  TX_FALSE;

    /* Loop to handle cases where the owner of the pool changed.  */
//    do
//    {
        /* Restore interrupts.  */
//        TX_RESTORE

        /* At this point, the executing thread owns the pool and can perform a search
           for free memory.  */
        work_ptr =  _tx_byte_pool_search(pool_ptr, memory_size);

        /* Lockout interrupts.  */
//        TX_DISABLE

        /* Determine if we are finished.  */
//        if (work_ptr != TX_NULL)
//        {
//            /* Yes, we have found a block the search is finished.  */
//            finished =  TX_TRUE;
//        } else {
//
//            /* No block was found, does this thread still own the pool?  */
//            if (pool_ptr -> tx_byte_pool_owner == thread_ptr)
//            {
//
//                /* Yes, then we have looked through the entire pool and haven't found the memory.  */
//                finished =  TX_TRUE;
//            }
//        }

//    } while (finished == TX_FALSE);

    /* Copy the pointer into the return destination.  */
    *memory_ptr =  (VOID *) work_ptr;

    /* Determine if memory was found.  */
    if (work_ptr != TX_NULL)
    {
        /* Restore interrupts.  */
//        TX_RESTORE

        /* Set the status to success.  */
        status =  TX_SUCCESS;
    }
    else
    {
        /* Restore interrupts.  */
//        TX_RESTORE

        /* Immediate return, return error completion.  */
        status =  TX_NO_MEMORY;
    }

    /* Return completion status.  */
    return(status);
}


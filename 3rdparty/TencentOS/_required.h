//
// Created by JianHang on 2022/2/14.
//

#ifndef C_MEM_LIB_3RDPARTY_TENCENTOS__REQUIRED_H_
#define C_MEM_LIB_3RDPARTY_TENCENTOS__REQUIRED_H_

#define TOS_CFG_MMHEAP_EN                   1
#define TOS_CFG_CPU_LEAD_ZEROS_ASM_PRESENT  0

#define __API__
#define __KNL__
#define __STATIC_INLINE__ static inline
#define __STATIC__ static

#define K_NULL  0
#define K_TRUE  1
#define K_FALSE 0

#define TOS_PTR_SANITY_CHECK(__PTR)
#define TOS_OFFSET_OF_FIELD(type, field) ((uint32_t)&(((type *)0)->field))

#include <stdint.h>
typedef enum k_err_en {
    K_ERR_NONE                                  = 0u,
    K_ERR_MMHEAP_INVALID_POOL_ADDR              = 800u,
    K_ERR_MMHEAP_INVALID_POOL_SIZE,
    K_ERR_MMHEAP_POOL_OVERFLOW,
    K_ERR_MMHEAP_POOL_ALREADY_EXIST,
    K_ERR_MMHEAP_POOL_NOT_EXIST
} k_err_t;

typedef uint32_t    cpu_addr_t;
typedef uint32_t    cpu_data_t;

#endif //C_MEM_LIB_3RDPARTY_TENCENTOS__REQUIRED_H_

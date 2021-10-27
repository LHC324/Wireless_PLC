/****************************************************************************
 * Copyright (c) [2021] [Soga] [core.zhang@outlook.com]                     *
 * [] is licensed under Mulan PSL v2.                                       *
 * You can use this software according to the terms and conditions of       *
 * the Mulan PSL v2.                                                        *
 * You may obtain a copy of Mulan PSL v2 at:                                *
 *          http://license.coscl.org.cn/MulanPSL2                           *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF     *
 * ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO        *
 * NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.       *
 * See the Mulan PSL v2 for more details.                                   *
 *                                                                          *
 ***************************************************************************/
#ifndef QUEUE_H
#define QUEUE_H
/* Includes --------------------------------------------------------*/
// #include <stdint.h>
// #include <stdbool.h>
#include <stdio.h>
#include "config.h"

/* Global define ---------------------------------------------------*/
#define END_DEF_QUEUE(__NAME)

/* Global macro ----------------------------------------------------*/
#define NONE_ATOM_ACCESS(__CODE)    {__CODE;}
#define SAFE_ATOM_ACCESS(__CODE)                                    \
    {                                                               \
        uint32_t wInterruptState = GET_GLOBAL_INTERRUPT_STATE();    \
        DISABLE_GLOBAL_INTERRUPT();                                 \
        __CODE;                                                     \
        RESTORE_GLOBAL_INTERRUPT_STATE(wInterruptState);            \
    }

#define QUEUE_NAME(__NAME)  __NAME##_queue_t

#define __DEF_QUEUE(__NAME, __TYPE, __PTR_TYPE, __MUTEX_TYPE, __ATOM_ACCESS_WRAP)  \
    typedef struct __##__NAME##_queue_t __NAME##_queue_t;           \
    struct __##__NAME##_queue_t {                                   \
        __PTR_TYPE tHead;                                           \
        __PTR_TYPE tTail;                                           \
        __PTR_TYPE tSize;                                           \
        __PTR_TYPE tLength;                                         \
        __PTR_TYPE tPeekedCount;                                    \
        __PTR_TYPE tPeekHead;                                       \
        __MUTEX_TYPE tMutex;                                        \
        __TYPE *ptBuffer;                                           \
    };                                                              \
                                                                    \
uint8_t __NAME##_queue_init(__NAME##_queue_t* ptQueue,                 \
                         __TYPE* ptBuffer, __PTR_TYPE tSize)        \
{                                                                   \
    __NAME##_queue_t* ptQ = (__NAME##_queue_t*)ptQueue;             \
    if ((ptQ == NULL) || (ptBuffer == NULL) || (tSize == 0)) {      \
        return false;                                               \
    }                                                               \
                                                                    \
    ptQ->ptBuffer = ptBuffer;                                       \
    ptQ->tSize = tSize;                                             \
    ptQ->tHead = 0;                                                 \
    ptQ->tTail = 0;                                                 \
    ptQ->tLength = 0;                                               \
    ptQ->tPeekedCount = 0;                                          \
    ptQ->tPeekHead = ptQ->tHead;                                    \
                                                                    \
    return true;                                                    \
}                                                                   \
                                                                    \
uint8_t __NAME##_queue_in(__NAME##_queue_t* ptQueue,                   \
                      const __TYPE *ptObj)                          \
{                                                                   \
    uint8_t bResult = false;                                           \
    __NAME##_queue_t* ptQ = (__NAME##_queue_t*)ptQueue;             \
    if ((ptQueue == NULL) || (ptObj == NULL)) {                     \
        return false;                                               \
    }                                                               \
                                                                    \
    __ATOM_ACCESS_WRAP (                                            \
        if (ptQ->tLength < ptQ->tSize) {                            \
            ptQ->tLength++;                                         \
            ptQ->ptBuffer[ptQ->tTail] = *ptObj;                     \
            if (ptQ->tTail == (ptQ->tSize - 1)) {                   \
                ptQ->tTail = 0;                                     \
            } else {                                                \
                ptQ->tTail++;                                       \
            }                                                       \
            bResult = true;                                         \
        }                                                           \
    )                                                               \
                                                                    \
    return bResult;                                                 \
}                                                                   \
                                                                    \
uint8_t __NAME##_queue_out(__NAME##_queue_t* ptQueue, __TYPE* ptObj)   \
{                                                                   \
    uint8_t bResult = false;                                           \
    __NAME##_queue_t* ptQ = (__NAME##_queue_t*)ptQueue;             \
    if ((ptQ == NULL) || (ptObj == NULL)) {                         \
        return false;                                               \
    }                                                               \
                                                                    \
    __ATOM_ACCESS_WRAP (                                            \
        if (ptQ->tLength) {                                         \
            ptQ->tLength--;                                         \
            *ptObj = ptQ->ptBuffer[ptQ->tHead];                     \
            if (ptQ->tHead == (ptQ->tSize - 1)) {                   \
                ptQ->tHead = 0;                                     \
            } else {                                                \
                ptQ->tHead++;                                       \
            }                                                       \
            ptQ->tPeekHead = ptQ->tHead;                            \
            ptQ->tPeekedCount = 0;                                  \
            bResult = true;                                         \
        }                                                           \
    )                                                               \
                                                                    \
    return bResult;                                                 \
}                                                                   \
                                                                    \
uint8_t __NAME##_queue_is_empty(__NAME##_queue_t* ptQueue)             \
{                                                                   \
    __NAME##_queue_t* ptQ = (__NAME##_queue_t*)ptQueue;             \
    if (ptQ == NULL) {                                              \
        return false;                                               \
    }                                                               \
                                                                    \
    return 0 == ptQueue->tLength;                                   \
}                                                                   \
                                                                    \
__PTR_TYPE __NAME##_queue_size(__NAME##_queue_t* ptQueue)           \
{                                                                   \
    __NAME##_queue_t* ptQ = (__NAME##_queue_t*)ptQueue;             \
    if (ptQ == NULL) {                                              \
        return 0;                                                   \
    }                                                               \
                                                                    \
    return ptQueue->tLength;                                        \
}                                                                   \
                                                                    \
uint8_t __NAME##_queue_peek(__NAME##_queue_t* ptQueue, __TYPE* ptObj)  \
{                                                                   \
    uint8_t bResult = false;                                           \
    __NAME##_queue_t* ptQ = (__NAME##_queue_t*)ptQueue;             \
    if ((ptQ == NULL) || (ptObj == NULL)) {                         \
        return false;                                               \
    }                                                               \
                                                                    \
    __ATOM_ACCESS_WRAP (                                            \
        if (ptQ->tPeekedCount < ptQ->tLength) {                     \
            *ptObj = ptQ->ptBuffer[ptQ->tPeekHead];                 \
            if (++ptQ->tPeekHead >= ptQ->tSize) {                   \
                ptQ->tPeekHead = 0;                                 \
            }                                                       \
            ptQ->tPeekedCount += 1;                                 \
            bResult = true;                                         \
        }                                                           \
    )                                                               \
                                                                    \
    return bResult;                                                 \
}                                                                   \
                                                                    \
uint8_t __NAME##_queue_reset_peek(__NAME##_queue_t* ptQueue)           \
{                                                                   \
    uint8_t bResult = false;                                           \
    __NAME##_queue_t* ptQ = (__NAME##_queue_t*)ptQueue;             \
    if (ptQ == NULL) {                                              \
        return false;                                               \
    }                                                               \
                                                                    \
    __ATOM_ACCESS_WRAP (                                            \
        ptQ->tPeekHead = ptQ->tHead;                                \
        ptQ->tPeekedCount = 0;                                      \
        bResult = true;                                             \
    )                                                               \
                                                                    \
    return bResult;                                                 \
}                                                                   \
                                                                    \
uint8_t __NAME##_queue_get_all_peeked(__NAME##_queue_t* ptQueue)       \
{                                                                   \
    uint8_t bResult = false;                                           \
    __NAME##_queue_t* ptQ = (__NAME##_queue_t*)ptQueue;             \
    if (ptQ == NULL) {                                              \
        return false;                                               \
    }                                                               \
                                                                    \
    __ATOM_ACCESS_WRAP (                                            \
        if (0 < ptQ->tPeekedCount) {                                \
            ptQ->tHead = ptQ->tPeekHead;                            \
            ptQ->tLength -= ptQ->tPeekedCount;                      \
            ptQ->tPeekedCount = 0;                                  \
        }                                                           \
        bResult = true;                                             \
    )                                                               \
                                                                    \
    return bResult;                                                 \
}

#define DEF_QUEUE(__NAME, __TYPE, __PTR_TYPE, __MUTEX_TYPE)         \
    __DEF_QUEUE(__NAME, __TYPE, __PTR_TYPE, __MUTEX_TYPE, NONE_ATOM_ACCESS)

#define DEF_SAFE_QUEUE(__NAME, __TYPE, __PTR_TYPE, __MUTEX_TYPE)    \
    __DEF_QUEUE(__NAME, __TYPE, __PTR_TYPE, __MUTEX_TYPE, SAFE_ATOM_ACCESS)

#define QUEUE_INIT(__NAME, __QUEUE, __BUFFER, __SIZE)               \
        __NAME##_queue_init((__QUEUE), (__BUFFER), (__SIZE))

#define QUEUE_IN(__NAME, __QUEUE, __VALUE_PTR)                      \
        __NAME##_queue_in((__QUEUE), (__VALUE_PTR))

#define QUEUE_OUT(__NAME, __QUEUE, __ADDR)                          \
        __NAME##_queue_out((__QUEUE), (__ADDR))

#define QUEUE_SIZE(__NAME, __QUEUE)                                 \
        __NAME##_queue_size((__QUEUE))

#define QUEUE_IS_EMPTY(__NAME, __QUEUE)                             \
        __NAME##_queue_is_empty((__QUEUE))

#define QUEUE_PEEK(__NAME, __QUEUE, __ADDR)                         \
        __NAME##_queue_peek((__QUEUE), (__ADDR))

#define QUEUE_RESET_PEEK(__NAME, __QUEUE)                           \
        __NAME##_queue_reset_peek((__QUEUE))

#define QUEUE_GET_ALL_PEEKED(__NAME, __QUEUE)                       \
        __NAME##_queue_get_all_peeked((__QUEUE))

/* Global typedef --------------------------------------------------*/
/* Global variables ------------------------------------------------*/
/* Global function prototypes --------------------------------------*/

#endif
/*************************** End of file ****************************/

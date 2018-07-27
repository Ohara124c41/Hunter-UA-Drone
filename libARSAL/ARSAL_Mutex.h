/*
    Copyright (C) 2014 Parrot SA

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the 
      distribution.
    * Neither the name of Parrot nor the names
      of its contributors may be used to endorse or promote products
      derived from this software without specific prior written
      permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
    COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
    OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
    AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
    OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.
*/
/**
 * @file libARSAL/ARSAL_Mutex.h
 * @brief This file contains headers about mutex abstraction layer
 * @date 05/18/2012
 * @author frederic.dhaeyer@parrot.com
 */
#ifndef _ARSAL_MUTEX_H_
#define _ARSAL_MUTEX_H_

/**
 * @brief Define a mutex type.
 */
typedef void* ARSAL_Mutex_t;

/**
 * @brief Define a condition type.
 */
typedef void* ARSAL_Cond_t;

/**
 * @brief Initializes a mutex.
 *
 * @param mutex The mutex to initialize
 * @retval On success, ARSAL_Mutex_Init() returns 0. Otherwise, it returns an error number (See errno.h)
 */
int ARSAL_Mutex_Init(ARSAL_Mutex_t *mutex);

/**
 * @brief Destroys a mutex
 *
 * @param mutex The mutex to destroy
 * @retval On success, ARSAL_Mutex_Destroy() returns 0. Otherwise, it returns an error number (See errno.h)
 */
int ARSAL_Mutex_Destroy(ARSAL_Mutex_t *mutex);

/**
 * @brief Locks a mutex
 *
 * @param mutex The mutex to lock
 * @retval On success, ARSAL_Mutex_Lock() returns 0. Otherwise, it returns an error number (See errno.h)
 */
int ARSAL_Mutex_Lock(ARSAL_Mutex_t *mutex);

/**
 * @brief Tries to lock a mutex
 *
 * @param mutex The mutex to lock
 * @retval On success, ARSAL_Mutex_Trylock() returns 0. Otherwise, it returns an error number (See errno.h)
 */
int ARSAL_Mutex_Trylock(ARSAL_Mutex_t *mutex);

/**
 * @brief Unlocks a mutex
 *
 * @param mutex The mutex to unlock
 * @retval On success, ARSAL_Mutex_Unlock() returns 0. Otherwise, it returns an error number (See errno.h)
 */
int ARSAL_Mutex_Unlock(ARSAL_Mutex_t *mutex);

/**
 * @brief Initializes a condition
 *
 * @param cond The condition to initialize
 * @retval On success, ARSAL_Cond_Init() returns 0. Otherwise, it returns an error number (See errno.h)
 */
int ARSAL_Cond_Init(ARSAL_Cond_t *cond);

/**
 * @brief Destroy a condition
 *
 * @param cond The condition to destroy
 * @retval On success, ARSAL_Cond_Destroy() returns 0. Otherwise, it returns an error number (See errno.h)
 */
int ARSAL_Cond_Destroy(ARSAL_Cond_t *cond);

/**
 * @brief Wait on a condition
 *
 * @param cond The condition to wait
 * @param mutex The mutex link to condition.
 * @retval On success, ARSAL_Cond_Wait() returns 0. Otherwise, it returns an error number (See errno.h)
 */
int ARSAL_Cond_Wait(ARSAL_Cond_t *cond, ARSAL_Mutex_t *mutex);

/**
 * @brief Wait on a condition and returns error
 *
 * @param cond The condition to wait
 * @param mutex The mutex linked to condition.
 * @param timeout The time (ms) to wait before ARSAL_Cond_Timedwait() returns ETIMEDOUT.
 * @retval On success, ARSAL_Cond_Timedwait() returns 0. If the time is specified by timeout has passed, ARSAL_Cond_Timedwait() returns ETIMEDOUT. Otherwise, it returns an error number (See errno.h)
 */
int ARSAL_Cond_Timedwait(ARSAL_Cond_t *cond, ARSAL_Mutex_t *mutex, int timeout);

/**
 * @brief Signal a condition
 *
 * @param cond The condition to signal
 * @retval On success, ARSAL_Cond_Signal() returns 0. Otherwise, it returns an error number (See errno.h)
 */
int ARSAL_Cond_Signal(ARSAL_Cond_t *cond);

/**
 * @brief Broadcast a condition
 *
 * @param cond The condition to broadcast
 * @retval On success, ARSAL_Cond_Broadcast() returns 0. Otherwise, it returns an error number (See errno.h)
 */
int ARSAL_Cond_Broadcast(ARSAL_Cond_t *cond);

#endif // _ARSAL_MUTEX_H_

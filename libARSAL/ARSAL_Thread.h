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
 * @file libARSAL/ARSAL_Thread.h
 * @brief This file contains headers about thread abstraction layer
 * @date 05/18/2012
 * @author frederic.dhaeyer@parrot.com
 */
#ifndef _ARSAL_THREAD_H_
#define _ARSAL_THREAD_H_

/**
 * @brief Define a thread type.
 */
typedef void* ARSAL_Thread_t;

/**
 * @brief Define a callback function type.
 */
typedef void* (*ARSAL_Thread_Routine_t) (void *);

/**
 * @brief Create a new thread
 *
 * @param thread The thread to create
 * @param routine The routine to invoke by thread
 * @param arg The argument passed to routine()
 * @retval On success, ARSAL_Thread_create() returns 0. Otherwise, it returns an error number (See errno.h)
 */
int ARSAL_Thread_Create(ARSAL_Thread_t *thread, ARSAL_Thread_Routine_t routine, void *arg);

/**
 * @brief Join a thread
 *
 * @param thread The thread to join
 * @param retval If this pointer is not NULL, the exit status is placed into *retval
 * @retval On success, ARSAL_Thread_join() returns 0. Otherwise, it returns an error number (See errno.h)
 */
int ARSAL_Thread_Join(ARSAL_Thread_t thread, void **retval);

/**
 * @brief Destroy a thread
 *
 * @param thread The thread to destroy
 * @retval On success, ARSAL_Thread_create() returns 0. Otherwise, it returns an error number (See errno.h)
 */
int ARSAL_Thread_Destroy(ARSAL_Thread_t *thread);

#endif // _ARSAL_THREAD_H_

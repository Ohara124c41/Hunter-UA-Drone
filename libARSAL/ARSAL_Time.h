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
 * @file libARSAL/ARSAL_Time.h
 * @brief This file contains headers about time abstraction layer
 * @date 05/18/2012
 * @author frederic.dhaeyer@parrot.com
 */
#ifndef _ARSAL_TIME_H_
#define _ARSAL_TIME_H_
#include <inttypes.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

/**
 * @brief Convert second to millisecond
 */
#define SEC_TO_MSEC(sec)    ((sec) * 1000)

/**
 * @brief Convert second to microsecond
 */
#define SEC_TO_USEC(sec)    ((sec) * 1000000)

/**
 * @brief Convert second to nanosecond
 */
#define SEC_TO_NSEC(sec)    ((sec) * 1000000000)

/**
 * @brief Convert millisecond to second
 */
#define MSEC_TO_SEC(msec)    ((msec) / 1000)

/**
 * @brief Convert millisecond to microsecond
 */
#define MSEC_TO_USEC(msec)    ((msec) * 1000)

/**
 * @brief Convert millisecond to nanosecond
 */
#define MSEC_TO_NSEC(msec)    ((msec) * 1000000)

/**
 * @brief Convert microsecond to second
 */
#define USEC_TO_SEC(usec)    ((usec) / 1000000)

/**
 * @brief Convert microsecond to millisecond
 */
#define USEC_TO_MSEC(usec)    ((usec) / 1000)

/**
 * @brief Convert microsecond to nanosecond
 */
#define USEC_TO_NSEC(usec)    ((usec) * 1000)

/**
 * @brief Convert nanosecond to second
 */
#define NSEC_TO_SEC(nsec)    ((nsec) / 1000000000)

/**
 * @brief Convert nanosecond to millisecond
 */
#define NSEC_TO_MSEC(nsec)    ((nsec) / 1000000)

/**
 * @brief Convert nanosecond to microsecond
 */
#define NSEC_TO_USEC(nsec)    ((nsec) / 1000)


#ifndef TIMEVAL_TO_TIMESPEC
/**
 * @brief Convert timeval structure to timespec structure
 */
#define TIMEVAL_TO_TIMESPEC(tv, ts)                 \
    do                                              \
    {                                               \
        (ts)->tv_sec = (tv)->tv_sec;                \
        (ts)->tv_nsec = USEC_TO_NSEC((tv)->tv_usec);\
    } while(0)
#endif

#ifndef TIMESPEC_TO_TIMEVAL
/**
 * @brief Convert timespec structure to timeval structure
 */
#define TIMESPEC_TO_TIMEVAL(ts, tv)                 \
    do                                              \
    {                                               \
        (tv)->tv_sec = (ts)->tv_sec;                \
        (tv)->tv_usec = NSEC_TO_USEC((ts)->tv_nsec);\
    } while(0)
#endif

/**
 * @brief Gets the current system time as a timespec
 *
 * @param res Pointer to a timespec struct which will be filled with the current time
 *
 * @note This function may return a non meaningful date, but is suitable for time interval calculations
 *
 * @return 0 if no error occured, -1 if any error occured
 */
int ARSAL_Time_GetTime(struct timespec *res);

/**
 * @brief Gets the current local time both as a struct timespec and as a struct tm.
 * This function is typically used for displaying a date to the user, where @ref{ARSAL_Time_GetTime}
 * may yield a non meaningful date.
 * @param res Pointer to a timespec struct which will hold the local time (optionnal, may be NULL)
 * @param localTime Pointer to a tm struct which will hold the local time (optionnal, may be NULL)
 * @warning The returned value is affected by discontinuous jumps in the system time (e.g., if the system administrator manually changes the clock), and by the incremental adjustments performed by adjtime(3) and NTP.
 * @return 0 if no error occures, -1 if any error occured
 */
int ARSAL_Time_GetLocalTime(struct timespec *res, struct tm *localTime);


/**
 * @brief Checks the equality of two timeval
 *
 * @param t1 First time to compare
 * @param t2 Second time to compare
 *
 * @return 1 if t1 and t2 represent the same value
 * @return 0 in all other cases
 */
int ARSAL_Time_TimevalEquals (struct timeval *t1, struct timeval *t2);


/**
 * @brief Checks the equality of two timespec
 *
 * @param t1 First time to compare
 * @param t2 Second time to compare
 *
 * @return 1 if t1 and t2 represent the same value
 * @return 0 in all other cases
 */
int ARSAL_Time_TimespecEquals (struct timespec *t1, struct timespec *t2);

/**
 * @brief Computes the difference between two timeval
 *
 * This function returns the time, in miliseconds, between the two
 * given timevals.
 *
 * @param start Start of the time interval to compute
 * @param end End of the time interval to compute
 * @return The number of ms between the two timeval. A negative number is an error
 * @warning Make sure that "end" is after "start"
 */
int32_t ARSAL_Time_ComputeTimevalMsTimeDiff (struct timeval *start, struct timeval *end);

/**
 * @brief Computes the difference between two timespec
 *
 * This function returns the time, in miliseconds, between the two
 * given timespecs.
 *
 * @param start Start of the time interval to compute
 * @param end End of the time interval to compute
 * @return The number of ms between the two timespec. A negative number is an error
 * @warning Make sure that "end" is after "start"
 */
int32_t ARSAL_Time_ComputeTimespecMsTimeDiff (struct timespec *start, struct timespec *end);

#endif // _ARSAL_TIME_H_

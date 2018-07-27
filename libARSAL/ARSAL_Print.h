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
 * @file libARSAL/ARSAL_Print.h
 * @brief This file contains headers about debug print abstraction layer
 * @date 06/01/2012
 * @author frederic.dhaeyer@parrot.com
 */
#ifndef _ARSAL_PRINT_H_
#define _ARSAL_PRINT_H_
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <libARSAL/ARSAL_Time.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/** Wrapper for gcc printf attribute */
#ifndef ARSAL_ATTRIBUTE_FORMAT_PRINTF
#  ifndef _MSC_VER
#    define ARSAL_ATTRIBUTE_FORMAT_PRINTF(_x, _y) \
        __attribute__((__format__(__printf__, _x, _y)))
#  else /* _MSC_VER */
#    define ARSAL_ATTRIBUTE_FORMAT_PRINTF(_x, _y)
#  endif /* _MSC_VER */
#endif /* !ARSAL_ATTRIBUTE_FORMAT_PRINTF */

/**
 * @brief Output level
 */
typedef enum
{
    ARSAL_PRINT_FATAL,    /**< The fatal level. The highest level, always printed */
    ARSAL_PRINT_ERROR,    /**< The error level. */
    ARSAL_PRINT_WARNING,  /**< The warning level. */
    ARSAL_PRINT_INFO,     /**< The info level. */
    ARSAL_PRINT_DEBUG,    /**< The debug level. */
    ARSAL_PRINT_VERBOSE,  /**< The verbose level. The lowest usable level */

    ARSAL_PRINT_MAX,      /**< The maximum of enum, do not use ! */
} eARSAL_PRINT_LEVEL;

#define     ARSAL_PRINT_DATE_STRING_LENGTH 9        // HH:MM:SS\0

/**
 * @brief Prints a specific output
 *
 * This is the default entry point for printing.
 * This function outputs a string of the following format:
 * `[LEVEL] TAG | HH:MM:SS:mmm | function:line - FORMAT`
 *
 * @param level The print level (eARSAL_PRINT_LEVEL enum)
 * @param tag A short tag which will prefix the log timestamp
 * @param format The format string to print
 * @param ... The format parameters
 */
#define ARSAL_PRINT(level, tag, format, ...) \
    ARSAL_Print_PrintRawEx(level, __FUNCTION__, __LINE__, tag, format, ##__VA_ARGS__)

/**
 * @brief Sets the minimum level of verbosity for logs.
 * Logs with a lower level won't appear.
 * Default is "ARSAL_PRINT_INFO" for release builds, "ARSAL_PRINT_VERBOSE" for debug builds.
 * @param level The minimum level for logs.
 * @return 0 If the minimum level was set, 1 Otherwise
 */
int ARSAL_Print_SetMinimumLevel(eARSAL_PRINT_LEVEL level);

/**
 * @brief Gets the minimum level of verbosity for logs.
 * Logs with a level inferior to that will be ignored
 * @return The current minimum level.
 */
eARSAL_PRINT_LEVEL ARSAL_Print_GetMinimumLevel(void);

/**
 * @brief Prints a formatted output
 * @warning This function should not be used directly
 * @see ARSAL_PRINT()
 *
 * @param level The level of output
 * @param tag The tag of the output
 * @param format output format
 * @retval On success, ARSAL_Print_PrintRaw() returns the number of characters printed. Otherwise, it returns a negative value.
 */
int ARSAL_Print_PrintRaw(eARSAL_PRINT_LEVEL level, const char *tag, const char *format, ...) ARSAL_ATTRIBUTE_FORMAT_PRINTF(3, 4);

/**
 * @brief Prints a formatted output. It prepend time, file and line and adds '\n' if needed
 * @warning This function should not be used directly
 * @see ARSAL_PRINT()
 *
 * @param level The level of output
 * @param tag The tag of the output
 * @param func The func of the output
 * @param line The line of the output
 * @param format output format
 * @retval On success, ARSAL_Print_PrintRawEx() returns the number of characters printed. Otherwise, it returns a negative value.
 */
int ARSAL_Print_PrintRawEx(eARSAL_PRINT_LEVEL level, const char *func, int line, const char *tag, const char *format, ...) ARSAL_ATTRIBUTE_FORMAT_PRINTF(5, 6);

/**
 * @brief Transform a level into an intelligible string
 * @param level The level of output
 * @retval A const string describing the level. If level is not known, returns the description of the FATAL level
 */
const char* ARSAL_Print_GetLevelDescription(eARSAL_PRINT_LEVEL level);

#include <stdarg.h>
typedef int (*ARSAL_Print_Callback_t) (eARSAL_PRINT_LEVEL level, const char *tag, const char *format, va_list va);
void ARSAL_Print_SetCallback( ARSAL_Print_Callback_t callback);

/**
 * @brief Dump data in a file.
 * @param file output file
 * @param tag 1-byte identifier of data.
 * @param data data buffer.
 * @param size size of data.
 * @param sizeDump size of data to actually dump. 0 to dump everything.
 * @param ts: timestamp of data. NULL to use current time
 */
void ARSAL_Print_DumpData(FILE *file, uint8_t tag, const void *data, size_t size, size_t sizeDump, const struct timespec *ts);

/**
 * @brief Do a rotation on files used as data dump.
 * @param basePath base path of the dump. <basePath> will be renamed in <basePath>.1, <basePath>.1 in <basePath>.2 and so on
 * @param count number of files to keep.
 */
void ARSAL_Print_DumpRotateFiles(const char *basePath, int count);

#endif // _ARSAL_PRINT_H_

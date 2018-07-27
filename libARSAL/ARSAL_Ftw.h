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
 * @file ARSAL_Ftw.h
 * @brief libARSAL Ftw header file.
 * @date 19/12/2013
 * @author david.flattin.ext@parrot.com
 **/

#ifndef _ARSAL_FTW_H_
#define _ARSAL_FTW_H_

#include <sys/stat.h>

 /**
 * @brief ARSAL_FTW_t structure equal to "struct FTW"
 * @param base The base is the offset of the filename
 * @param level The level of the file
 * @see ARSAL_Nftw (), struct FTW
 */
typedef struct _ARSAL_FTW_t
{
    int base;
    int level;
} ARSAL_FTW_t;

/**
 * @brief FTW file type enum
 * @see ftw, nftw
 */
typedef enum
{
    ARSAL_FTW_F = 0,
    ARSAL_FTW_D,
} eARSAL_FTW_TYPE;

/**
 * @brief ARSAL_Nftw enum flags
 * @see nftw
 */
typedef enum
{
    ARSAL_FTW_NOFLAGS = 0,
    ARSAL_FTW_ACTIONRETVAL = 16,
} eARSAL_FTW_FLAG;

/**
 * @brief ARSAL_Nftw enum callback return values
 * @see nftw
 */
typedef enum
{
    ARSAL_FTW_CONTINUE = 0,
    ARSAL_FTW_STOP = 1,
    ARSAL_FTW_SKIP_SUBTREE = 2,
} eARSAL_FTW_RETURN;


/**
 * @brief User Callback called for each file discover in the directory hierarchy
 * @param fpath The path of the file
 * @param sb The stat structure returned by a call to stat()
 * @param typeflag The type of file found
 * @retval On success, returns 0. Otherwise, it returns user value
 * @see ARSAL_Ftw (), ftw standard documentation
 */
typedef int (*ARSAL_FtwCallback) (const char *fpath, const struct stat *sb, eARSAL_FTW_TYPE typeflag);

/**
 * @brief User Callback called for each file discover in the directory hierarchy
 * @param fpath The path of the file
 * @param sb The stat structure returned by a call to stat()
 * @param typeflag The type of file found
 * @param ftwbuf The 
 * @retval On success, returns 0. Otherwise, it returns user value
 * @see ARSAL_Nftw (), nftw standard documentation
 */
typedef int (*ARSAL_NftwCallback) (const char *fpath, const struct stat *sb, eARSAL_FTW_TYPE typeflag, ARSAL_FTW_t *ftwbuf);

/**
 * @brief Recursively descends the directory hierarchy
 * @param dirpath The directory to descend
 * @param cb The callback recursively on each element of run through the directories
 * @param nopenfd The maximum number of directories depth
 * @retval On success, returns 0. Otherwise, it returns -1, or callack user value
 * @see ftw standard documentation
 */
int ARSAL_Ftw(const char *dirpath, ARSAL_FtwCallback cb, int nopenfd);

/**
 * @brief Recursively descends the directory hierarchy
 * @param dirpath The directory to descend
 * @param cb The callback recursively on each element of run through the directories
 * @param nopenfd The maximum number of directories depth
 * @param flags The flag of the type of tree explore
 * @retval On success, returns 0. Otherwise, it returns -1, or callack user value
 * @see nftw standard documentation
 */
int ARSAL_Nftw(const char *dirpath, ARSAL_NftwCallback cb, int nopenfd, eARSAL_FTW_FLAG flags);

#endif /* _ARSAL_FTW_H_ */



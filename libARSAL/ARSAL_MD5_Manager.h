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
 * @file ARSAL_MD5.h
 * @brief libARSAL MD5 header file.
 * @date 02/06/2014
 * @author david.flattin.ext@parrot.com
 **/

#ifndef _ARSAL_MD5_H_
#define _ARSAL_MD5_H_

#include "libARSAL/ARSAL_Error.h"

#define ARSAL_MD5_LENGTH        16

/**
 * @brief Check an MD5
 * @param filePath The file path onto check its md5
 * @param md5 The md5 string
 * @param md5Len md5 string length
 * @retval On success, returns ARSAL_OK. Otherwise, it returns an error number of eARSAL_ERROR
 * @see ARSAL_MD5_Manager_Init ()
 */
typedef eARSAL_ERROR (*ARSAL_MD5_Check_t)(void *md5Object, const char *filePath, const char *md5);

/**
 * @brief Compute an MD5
 * @param filePath The file path onto check its md5
 * @param[out] md5 The md5 string to receive the md5
 * @param md5Len md5 string buffer length
 * @retval On success, returns ARSAL_OK. Otherwise, it returns an error number of eARSAL_ERROR
 * @see ARSAL_MD5_Manager_Init ()
 */
typedef eARSAL_ERROR (*ARSAL_MD5_Compute_t)(void *md5Object, const char *filePath, uint8_t *md5, int md5Len);

/**
 * @brief MD5 Manager structure
 * @retval md5Check The Check function
 * @retval md5Compute The Compute function
 * @retval md5Object The md5 object
 * @see ARSAL_MD5_Manager_New
 */
typedef struct _ARSAL_MD5_Manager_t 
{
    ARSAL_MD5_Check_t md5Check;
    ARSAL_MD5_Compute_t md5Compute;
    void *md5Object;
} ARSAL_MD5_Manager_t;


/**
 * @brief Create a new ARSAL MD5 Manager
 * @warning This function allocates memory
 * @param[out] error A pointer on the error output
 * @return Pointer on the new ARSAL MD5 Manager
 * @see ARSAL_MD5_Manager_Delete ()
 */
ARSAL_MD5_Manager_t* ARSAL_MD5_Manager_New(eARSAL_ERROR *error);

/**
 * @brief Delete an ARSAL MD5 Manager
 * @warning This function frees memory
 * @param manager The address of the pointer on the ARSAL MD5 Manager
 * @see ARSAL_MD5_Manager_New ()
 */
void ARSAL_MD5_Manager_Delete(ARSAL_MD5_Manager_t **managerAddr);

/**
 * @brief Initialize an ARSAL MD5 Manager
 * @param manager The MD5 Manager
 * @retval On success, returns ARSAL_OK. Otherwise, it returns an error number of eARSAL_ERROR
 * @see ARSAL_MD5_Manager_Close ()
 */
eARSAL_ERROR ARSAL_MD5_Manager_Init(ARSAL_MD5_Manager_t *manager);

/**
 * @brief Close an ARSAL MD5 Manager
 * @param manager The MD5 Manager
 * @retval On success, returns ARSAL_OK. Otherwise, it returns an error number of eARSAL_ERROR
 * @see ARSAL_MD5_Manager_Init ()
 */
void ARSAL_MD5_Manager_Close(ARSAL_MD5_Manager_t *manager);

/**
 * @brief Check an MD5
 * @param manager The MD5 Manager
 * @param filePath The file path onto check its md5
 * @param md5 The md5 string
 * @param md5Len md5 string length
 * @retval On success, returns ARSAL_OK. Otherwise, it returns an error number of eARSAL_ERROR
 * @see ARSAL_MD5_Manager_New ()
 */
eARSAL_ERROR ARSAL_MD5_Manager_Check(ARSAL_MD5_Manager_t *manager, const char *filePath, const char *md5Txt);

/**
 * @brief Compute an MD5
 * @param manager The MD5 Manager
 * @param filePath The file path onto check its md5
 * @param[out] md5 The md5 string to receive the md5
 * @param md5Len md5 string buffer length
 * @retval On success, returns ARSAL_OK. Otherwise, it returns an error number of eARSAL_ERROR
 * @see ARSAL_MD5_Manager_New ()
 */
eARSAL_ERROR ARSAL_MD5_Manager_Compute(ARSAL_MD5_Manager_t *manager, const char *filePath, uint8_t *md5, int md5Size);


#endif /* _ARSAL_MD5_H_ */



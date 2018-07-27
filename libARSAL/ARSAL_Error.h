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
#ifndef _ARSAL_ERROR_H_
#define _ARSAL_ERROR_H_

/**
 * @brief libARSAL errors known.
 */
typedef enum
{
    ARSAL_OK = 0,                              /**< No error */

    ARSAL_ERROR = -1000,                       /**< ARSAL Generic error */
    ARSAL_ERROR_ALLOC,                         /**< ARSAL alloc error */
    ARSAL_ERROR_SYSTEM,                        /**< ARSAL system error */
    ARSAL_ERROR_BAD_PARAMETER,                 /**< ARSAL bad parameter error */
    ARSAL_ERROR_FILE,                          /**< ARSAL file error */
    
    ARSAL_ERROR_MD5 = -2000,                   /**< ARSAL md5 error */

    ARSAL_ERROR_BLE_CONNECTION = -5000,        /**< BLE connection generic error */
    ARSAL_ERROR_BLE_NOT_CONNECTED,             /**< BLE is not connected */
    ARSAL_ERROR_BLE_DISCONNECTION,             /**< BLE disconnection error */
    ARSAL_ERROR_BLE_SERVICES_DISCOVERING,      /**< BLE network services discovering error */
    ARSAL_ERROR_BLE_CHARACTERISTICS_DISCOVERING,    /**< BLE network characteristics discovering error */
    ARSAL_ERROR_BLE_CHARACTERISTIC_CONFIGURING,     /**< BLE network characteristic configuring error */
    ARSAL_ERROR_BLE_STACK,                          /**< BLE stack generic error */
    ARSAL_ERROR_BLE_TIMEOUT,                       /**< BLE timeout */
    ARSAL_ERROR_BLE_NO_DATA,                       /**< BLE no data */

} eARSAL_ERROR;

/**
 * @brief Gets the error string associated with an eARSAL_ERROR
 * @param error The error to describe
 * @return A static string describing the error
 *
 * @note User should NEVER try to modify a returned string
 */
const char* ARSAL_Error_ToString (eARSAL_ERROR error);

#endif /* _ARSAL_ERROR_H_ */



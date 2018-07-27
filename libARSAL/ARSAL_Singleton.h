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
 * @file  ARSAL_Singleton.h
 * @brief headers to define singletons.
 * @date 06/11/2013
 * @author frederic.dhaeyer@parrot.com
 */

#ifndef _ARSAL_SINGLETON_PRIVATE_H_
#define _ARSAL_SINGLETON_PRIVATE_H_

#define SYNTHESIZE_SINGLETON_FOR_CLASS(classname, initFunc) \
+ (classname *)shared##classname                            \
{                                                           \
    static classname *shared##classname = nil;              \
    static dispatch_once_t onceToken;                       \
    dispatch_once(&onceToken, ^{                            \
        shared##classname = [[classname alloc] init];       \
        [shared##classname initFunc];                       \
    });                                                     \
                                                            \
    return shared##classname;                               \
}

#define DECLARE_SINGLETON_FOR_CLASS(classname)              \
+ (classname *)shared##classname;

#define SINGLETON_FOR_CLASS(classname)                      \
[classname shared##classname]

#endif /** _ARSAL_SINGLETON_PRIVATE_H_ */

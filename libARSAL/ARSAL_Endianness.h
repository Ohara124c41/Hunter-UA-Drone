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
 * @file libARSAL/ARSAL_Endianness.h
 * @brief This file contains headers about endianness abstraction layer
 * @date 11/14/2012
 * @author nicolas.brulez@parrot.com
 */
#ifndef _ARSAL_ENDIANNESS_H_
#define _ARSAL_ENDIANNESS_H_

#include <inttypes.h>

#ifdef __APPLE__ // Apple use a different method for endianness handling

#include <architecture/byte_order.h>
#include <libkern/OSByteOrder.h>

/**
 * @brief Define little endian macro to the same values as linux <endian.h>
 */
#ifndef __LITTLE_ENDIAN
# define __LITTLE_ENDIAN 1234
#endif

/**
 * @brief Define big endian macro to the same values as linux <endian.h>
 */
#ifndef __BIG_ENDIAN
# define __BIG_ENDIAN 4321
#endif

/**
 * @brief Define pdp endian macro to the same values as linux <endian.h>
 */
#ifndef __PDP_ENDIAN
# define __PDP_ENDIAN 3412
#endif

/**
 * @brief Device endianness
 */
#ifndef __DEVICE_ENDIAN
# define __DEVICE_ENDIAN __LITTLE_ENDIAN
#endif

/**
 * @brief Opposite endiannes
 */
#ifndef __INVER_ENDIAN
# if __DEVICE_ENDIAN == __LITTLE_ENDIAN
#  define __INVER_ENDIAN __BIG_ENDIAN
# elif __DEVICE_ENDIAN == __BIG_ENDIAN
#  define __INVER_ENDIAN __LITTLE_ENDIAN
# else
#  error Device endian __PDP_ENDIAN not supported
# endif
#endif

#if __DEVICE_ENDIAN == __LITTLE_ENDIAN
/*
 * HOST --> DEVICE Conversion macros
 */

/**
 * @brief Convert a short int (2 bytes) to device endianness
 */
#define htods(v) OSSwapHostToLittleInt16(v)
/**
 * @brief Convert a long int (4 bytes) to device endianness
 */
#define htodl(v) OSSwapHostToLittleInt32(v)
/**
 * @brief Convert a long long int (8 bytes) to device endianness
 */
#define htodll(v) OSSwapHostToLittleInt64(v)
/**
 * @brief Convert a IEEE-754 float (4 bytes) to device endianness
 */
#define htodf(v) ARSAL_Endianness_SwapHostToLittleFloat(v)
/**
 * @brief Convert a IEEE-754 double (8 bytes) to device endianness
 */
#define htodd(v) ARSAL_Endianness_SwapHostToLittleDouble(v)

/*
 * DEVICE --> HOST Conversion macros
 */

/**
 * @brief Convert a short int (2 bytes) from device endianness
 */
#define dtohs(v) OSSwapLittleToHostInt16(v)
/**
 * @brief Convert a long int (4 bytes) from device endianness
 */
#define dtohl(v) OSSwapLittleToHostInt32(v)
/**
 * @brief Convert a long long int (8 bytes) from device endianness
 */
#define dtohll(v) OSSwapLittleToHostInt64(v)
/**
 * @brief Convert a IEEE-754 float (4 bytes) from device endianness
 */
#define dtohf(v) ARSAL_Endianness_SwapLittleToHostFloat(v)
/**
 * @brief Convert a IEEE-754 double (8 bytes) from device endianness
 */
#define dtohd(v) ARSAL_Endianness_SwapLittleToHostDouble(v)

#elif __DEVICE_ENDIAN == __BIG_ENDIAN
/*
 * HOST --> DEVICE Conversion macros
 */

/**
 * @brief Convert a short int (2 bytes) to device endianness
 */
#define htods(v) OSSwapHostToBigInt16(v)
/**
 * @brief Convert a long int (4 bytes) to device endianness
 */
#define htodl(v) OSSwapHostToBigInt32(v)
/**
 * @brief Convert a long long int (8 bytes) to device endianness
 */
#define htodll(v) OSSwapHostToBigInt64(v)
/**
 * @brief Convert a IEEE-754 float (4 bytes) to device endianness
 */
#define htodf(v) ARSAL_Endianness_SwapHostToBigFloat(v)
/**
 * @brief Convert a IEEE-754 double (8 bytes) to device endianness
 */
#define htodd(v) ARSAL_Endianness_SwapHostToBigDouble(v)

/*
 * DEVICE --> HOST Conversion macros
 */

/**
 * @brief Convert a short int (2 bytes) from device endianness
 */
#define dtohs(v) OSSwapBigToHostInt16(v)
/**
 * @brief Convert a long int (4 bytes) from device endianness
 */
#define dtohl(v) OSSwapBigToHostInt32(v)
/**
 * @brief Convert a long long int (8 bytes) from device endianness
 */
#define dtohll(v) OSSwapBigToHostInt64(v)
/**
 * @brief Convert a IEEE-754 float (4 bytes) from device endianness
 */
#define dtohf(v) ARSAL_Endianness_SwapBigToHostFloat(v)
/**
 * @brief Convert a IEEE-754 double (8 bytes) from device endianness
 */
#define dtohd(v) ARSAL_Endianness_SwapBigToHostDouble(v)

#else
# error Device PDP endianness is not supported
#endif


#if !defined(OS_INLINE)
# if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#        define OS_INLINE static inline
# else
#        define OS_INLINE static __inline__
# endif
#endif

/**
 * @brief INTERNAL_FUNCTION - Swap a float value from host to little endian
 * @param orig Initial host endian value to swap
 * @return little endian value of orig
 */
OS_INLINE
float
ARSAL_Endianness_SwapHostToLittleFloat (float orig)
{
    union fconv {
        float f;
        uint32_t i;
    } u;
    u.f = orig;
    u.i = OSSwapHostToLittleInt32 (u.i);
    return u.f;
}

/**
 * @brief INTERNAL_FUNCTION - Swap a float value from little to host endian
 * @param orig Initial little endian value to swap
 * @return host endian value of orig
 */
OS_INLINE
float
ARSAL_Endianness_SwapLittleToHostFloat (float orig)
{
    union fconv {
        float f;
        uint32_t i;
    } u;
    u.f = orig;
    u.i = OSSwapLittleToHostInt32 (u.i);
    return u.f;
}

/**
 * @brief INTERNAL_FUNCTION - Swap a float value from host to big endian
 * @param orig Initial host endian value to swap
 * @return big endian value of orig
 */
OS_INLINE
float
ARSAL_Endianness_SwapHostToBigFloat (float orig)
{
    union fconv {
        float f;
        uint32_t i;
    } u;
    u.f = orig;
    u.i = OSSwapHostToBigInt32 (u.i);
    return u.f;
}

/**
 * @brief INTERNAL_FUNCTION - Swap a float value from big to host endian
 * @param orig Initial big endian value to swap
 * @return host endian value of orig
 */
OS_INLINE
float
ARSAL_Endianness_SwapBigToHostFloat (float orig)
{
    union fconv {
        float f;
        uint32_t i;
    } u;
    u.f = orig;
    u.i = OSSwapBigToHostInt32 (u.i);
    return u.f;
}

/**
 * @brief INTERNAL_FUNCTION - Swap a double value from host to little endian
 * @param orig Initial host endian value to swap
 * @return little endian value of orig
 */
OS_INLINE
double
ARSAL_Endianness_SwapHostToLittleDouble (double orig)
{
    union dconv {
        double d;
        uint64_t i;
    } u;
    u.d = orig;
    u.i = OSSwapHostToLittleInt64 (u.i);
    return u.d;
}

/**
 * @brief INTERNAL_FUNCTION - Swap a double value from little to host endian
 * @param orig Initial little endian value to swap
 * @return host endian value of orig
 */
OS_INLINE
double
ARSAL_Endianness_SwapLittleToHostDouble (double orig)
{
    union dconv {
        double d;
        uint64_t i;
    } u;
    u.d = orig;
    u.i = OSSwapLittleToHostInt64 (u.i);
    return u.d;
}

/**
 * @brief INTERNAL_FUNCTION - Swap a double value from host to big endian
 * @param orig Initial host endian value to swap
 * @return big endian value of orig
 */
OS_INLINE
double
ARSAL_Endianness_SwapHostToBigDouble (double orig)
{
    union dconv {
        double d;
        uint64_t i;
    } u;
    u.d = orig;
    u.i = OSSwapHostToBigInt64 (u.i);
    return u.d;
}

/**
 * @brief INTERNAL_FUNCTION - Swap a double value from big to host endian
 * @param orig Initial big endian value to swap
 * @return host endian value of orig
 */
OS_INLINE
double
ARSAL_Endianness_SwapBigToHostDouble (double orig)
{
    union dconv {
        double d;
        uint64_t i;
    } u;
    u.d = orig;
    u.i = OSSwapBigToHostInt64 (u.i);
    return u.d;
}

#else // ! defined (__APPLE__)

#include <endian.h>

/**
 * @brief Device endianness
 */
#ifndef __DEVICE_ENDIAN
# define __DEVICE_ENDIAN __LITTLE_ENDIAN
#endif

/**
 * @brief Opposite endiannes
 */
#ifndef __INVER_ENDIAN
# if __DEVICE_ENDIAN == __LITTLE_ENDIAN
#  define __INVER_ENDIAN __BIG_ENDIAN
# elif __DEVICE_ENDIAN == __BIG_ENDIAN
#  define __INVER_ENDIAN __LITTLE_ENDIAN
# else
#  error Device endian __PDP_ENDIAN not supported
# endif
#endif

#if __BYTE_ORDER == __DEVICE_ENDIAN
/*
 * HOST --> DEVICE Conversion macros
 */

/**
 * @brief Convert a short int (2 bytes) to device endianness
 */
#define htods(v) (v)
/**
 * @brief Convert a long int (4 bytes) to device endianness
 */
#define htodl(v) (v)
/**
 * @brief Convert a long long int (8 bytes) to device endianness
 */
#define htodll(v) (v)
/**
 * @brief Convert a IEEE-754 float (4 bytes) to device endianness
 */
#define htodf(v) (v)
/**
 * @brief Convert a IEEE-754 double (8 bytes) to device endianness
 */
#define htodd(v) (v)

/*
 * DEVICE --> HOST Conversion macros
 */

/**
 * @brief Convert a short int (2 bytes) from device endianness
 */
#define dtohs(v) (v)
/**
 * @brief Convert a long int (4 bytes) from device endianness
 */
#define dtohl(v) (v)
/**
 * @brief Convert a long long int (8 bytes) from device endianness
 */
#define dtohll(v) (v)
/**
 * @brief Convert a IEEE-754 float (4 bytes) from device endianness
 */
#define dtohf(v) (v)
/**
 * @brief Convert a IEEE-754 double (8 bytes) from device endianness
 */
#define dtohd(v) (v)

#elif __BYTE_ORDER == __INVER_ENDIAN
/*
 * HOST --> DEVICE Conversion macros
 */

/**
 * @brief Convert a short int (2 bytes) to device endianness
 */
#define htods(v) (__typeof__ (v))ARSAL_Endianness_bswaps((uint16_t)v)
/**
 * @brief Convert a long int (4 bytes) to device endianness
 */
#define htodl(v) (__typeof__ (v))ARSAL_Endianness_bswapl((uint32_t)v)
/**
 * @brief Convert a long long int (8 bytes) to device endianness
 */
#define htodll(v) (__typeof__ (v))ARSAL_Endianness_bswapll((uint64_t)v)
/**
 * @brief Convert a IEEE-754 float (4 bytes) to device endianness
 */
#define htodf(v) (__typeof__ (v))ARSAL_Endianness_bswapf((float)v)
/**
 * @brief Convert a IEEE-754 double (8 bytes) to device endianness
 */
#define htodd(v) (__typeof__ (v))ARSAL_Endianness_bswapd((double)v)

/*
 * DEVICE --> HOST Conversion macros
 */

/**
 * @brief Convert a short int (2 bytes) from device endianness
 */
#define dtohs(v) (__typeof__ (v))ARSAL_Endianness_bswaps((uint16_t)v)
/**
 * @brief Convert a long int (4 bytes) from device endianness
 */
#define dtohl(v) (__typeof__ (v))ARSAL_Endianness_bswapl((uint32_t)v)
/**
 * @brief Convert a long long int (8 bytes) from device endianness
 */
#define dtohll(v) (__typeof__ (v))ARSAL_Endianness_bswapll((uint64_t)v)
/**
 * @brief Convert a IEEE-754 float (4 bytes) from device endianness
 */
#define dtohf(v) (__typeof__ (v))ARSAL_Endianness_bswapf((float)v)
/**
 * @brief Convert a IEEE-754 double (8 bytes) from device endianness
 */
#define dtohd(v) (__typeof__ (v))ARSAL_Endianness_bswapd((double)v)

/*
 * INTERNAL FUNCTIONS --- DO NOT USE THEM DIRECTLY
 */

/**
 * @brief INTERNAL FUNCTION : Swap byte order of a short int
 * @param orig Initial value
 * @return Swapped value
 */
static inline uint16_t ARSAL_Endianness_bswaps (uint16_t orig)
{
    return ((orig & 0xFF00) >> 8) | ((orig & 0x00FF) << 8);
}

/**
 * @brief INTERNAL FUNCTION : Swap byte order of a long int
 * @param orig Initial value
 * @return Swapped value
 */
static inline uint32_t ARSAL_Endianness_bswapl (uint32_t orig)
{
    return ((orig & 0xFF000000) >> 24) | ((orig & 0x00FF0000) >> 8) | ((orig & 0x0000FF00) << 8) | ((orig & 0x000000FF) << 24);
}

/**
 * @brief INTERNAL FUNCTION : Swap byte order of a long long int
 * @param orig Initial value
 * @return Swapped value
 */
static inline uint64_t ARSAL_Endianness_bswapll (uint64_t orig)
{
    return ((orig << 56) |
            ((orig << 40) & 0xff000000000000ULL) |
            ((orig << 24) & 0xff0000000000ULL) |
            ((orig << 8)  & 0xff00000000ULL) |
            ((orig >> 8)  & 0xff000000ULL) |
            ((orig >> 24) & 0xff0000ULL) |
            ((orig >> 40) & 0xff00ULL) |
            (orig >> 56));
}

/**
 * @brief INTERNAL FUNCTION : Swap byte order of a IEEE-754 float
 * @param orig Initial value
 * @return Swapped value
 */
static inline float ARSAL_Endianness_bswapf (float orig)
{
    uint32_t res = ARSAL_Endianness_bswapl (*(uint32_t*)&orig);
    return *(float *)&res;
}

/**
 * @brief INTERNAL FUNCTION : Swap byte order of a IEEE-754 double
 * @param orig Initial value
 * @return Swapped value
 */
static inline double ARSAL_Endianness_bswapd (double orig)
{
    uint64_t res = ARSAL_Endianness_bswapll (*(uint64_t*)&orig);
    return *(double *)&res;
}

#else // __BYTE_ORDER in neither LITTLE nor BIG endian
#error PDP Byte endianness not supported
#endif // __BYTE_ORDER

#endif // __APPLE__

#endif /* _ARSAL_ENDIANNESS_H_ */

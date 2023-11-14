#ifndef OPENCL_HOSTDEVICEHEADERS_OPENCL_ADDITIONAL_TYPES_H_
#define OPENCL_HOSTDEVICEHEADERS_OPENCL_ADDITIONAL_TYPES_H_

#include "opencl_syntax.h"

#define DEBUG 0

#if DEBUG | ___CLION_IDE__
    #define printfDebug printf
#else
    #define printfDebug(x, ...)
#endif

/* Note: long is *always* 64-bit in OpenCL */
typedef uchar uint8_t;
typedef char int8_t;
typedef ushort uint16_t;
typedef short int16_t;
typedef uint uint32_t;
typedef int int32_t;
typedef ulong uint64_t;
typedef long int64_t;

typedef char cl_char;
typedef uchar cl_uchar;
typedef short cl_short;
typedef ushort cl_ushort;
typedef int cl_int;
typedef uint cl_uint;
typedef long cl_long;
typedef ulong cl_ulong;
typedef float cl_float;
typedef double cl_double;
typedef half cl_half;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wincompatible-library-redeclaration"

void memcpy(__generic void *const dst, __generic const void *const src, uint32_t const size) {
    __generic uint8_t *const d = (uint8_t *) dst;
    __generic const uint8_t *const s = (uint8_t *) src;

    for (uint32_t i = 0; i < size; i++) {
        d[i] = s[i];
    }
}
#pragma clang diagnostic pop

void memcpy_c(__generic void *const dst, __constant void *const src, uint32_t const size) {
    uint8_t *const d = (uint8_t *) dst;
    __constant const uint8_t *const s = (__constant uint8_t *) src;

    for (uint32_t i = 0; i < size; i++) {
        d[i] = s[i];
    }
}

void reverse_bytes_order(__generic void *const dst, __generic const void *const src, uint32_t const size) {
    __generic uint8_t *const d = (uint8_t *) dst;
    __generic const uint8_t *const s = (uint8_t *) src;

    for (uint i = 0; i < size; i++) {
        d[i] = s[size - 1 - i];
    }
}

uint64_t reverse_bytes_order_uint64_t_ret(uint64_t num) {
    uint64_t ret;
    __generic uint8_t *const d = (uint8_t *) &ret;
    __generic const uint8_t *const s = (uint8_t *) &num;

    __attribute__((opencl_unroll_hint(sizeof(uint64_t))))
    for (uint i = 0; i < 8; i++) {
        d[i] = s[8 - 1 - i];
    };

    return ret;
}

void memset(void *dest, uint8_t val, uint64_t size) {
    unsigned char *ptr = (unsigned char *) dest;
    while (size-- > 0)
        *ptr++ = val;

}

inline void endianSwapEight(void *from, void *to) {
    for (uint i = 0; i < 8; i++) {
        //printf("!%c ", 48+((uint8_t*)from)[7 - i]);
        ((uint8_t *) to)[i] = ((uint8_t *) from)[7 - i];
        //((uint8_t*)to)[i] = ((uint8_t*)from)[i];
    }
}

inline void endianSwapEightReverse(void *src) {
    uint8_t *src_ptr = (uint8_t *) src;
    uint8_t tmp;
    for (uint i = 0; i < 8; i++) {
        tmp = src_ptr[i];
        src_ptr[i] = src_ptr[7 - i];
        src_ptr[7 - i] = tmp;
    }
}

__constant const char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                  '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

void toHex(const uint8_t bin, char *out) {
    out[0] = hexmap[(bin & 0xF0) >> 4];
    out[1] = hexmap[bin & 0x0F];
}

#if DEBUG
void printhex(const void *const bin, int const size) {

    uint8_t *b = (uint8_t *) bin;
    for (int i = 0; i < size; i++) {
        printfDebug
            ("%02x ", b[i]);
    }
    printfDebug
        ("\n");
}
#else
    #define printhex(...)
#endif

#endif //OPENCL_HOSTDEVICEHEADERS_OPENCL_ADDITIONAL_TYPES_H_
#ifndef __TOOLS_H
#define __TOOLS_H

#include <stdint.h>

#define arrlen(_arr) (sizeof(_arr) / sizeof((_arr)[0]))
#define str2uint(char1, char2, char3, char4) \
    ((char1 << 24) + (char2 << 16) + (char3 << 8) + char4)

inline static void arr_clear_u8(void *arr, uint32_t len)
{
    uint8_t *p = arr;
    do {
        *p++ = 0;
    } while (--len);
}

inline static void arr_clear_u16(void *arr, uint32_t len)
{
    uint16_t *p = arr;
    do {
        *p++ = 0;
    } while (--len);
}

inline static void arr_clear_u32(void *arr, uint32_t len)
{
    uint32_t *p = arr;
    do {
        *p++ = 0;
    } while (--len);
}

inline static void memcpy_u8(void *src, void *dst, uint32_t size)
{
    uint8_t *s = src;
    uint8_t *d = dst;
    do {
        *d++ = *s++;
    } while (--size);
}

inline static void memcpy_u16(void *src, void *dst, uint32_t size)
{
    size >>= 1;
    uint16_t *s = src;
    uint16_t *d = dst;
    do {
        *d++ = *s++;
    } while (--size);
}

inline static void memcpy_u32(void *src, void *dst, uint32_t size)
{
    size >>= 2;
    uint32_t *s = src;
    uint32_t *d = dst;
    do {
        *d++ = *s++;
    } while (--size);
}

#endif

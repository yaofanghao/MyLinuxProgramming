/*
 * @Author: yao fanghao
 * @Date: 2023-05-07 10:34:49
 * @LastEditTime: 2023-05-07 11:18:29
 * @LastEditors: yao fanghao
 */
#include <stdio.h>
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

void memset(void* dst_, uint8_t value, uint32_t size)
{
    ASSERT(dst_ != NULL);
    uint8_t* dst = (uint8_t*)dst_;
    while(size--)
    {
        *dst++ = value;
    }
}

void* memcpy_v1(void* dst, const void* src, size_t len) {
    uint8_t* d = (uint8_t*) dst;
    const uint8_t* s = (const uint8_t*) src;
    while(len--)
    {
        *d++ = *s++; 
    }
}

void* memcpy_v2(void* dst, const void* src, size_t len) {
    uint8_t* d = (uint8_t*) dst;
    const uint8_t* s = (const uint8_t*) src;
    
    size_t i = 0;
    for (; i + 4 < len; i += 4, d = d + 4, s = s + 4) {
        *d = *s;
        *(d + 1) = *(s + 1);
        *(d + 2) = *(s + 2);
        *(d + 3) = *(s + 3);
    }
}

int main()
{
    char* dst = "";
    char* src = "abcdef";

}
/*
 * @Author: yao fanghao
 * @Date: 2023-05-07 10:34:49
 * @LastEditTime: 2023-08-10 21:44:02
 * @LastEditors: yao fanghao
 */
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

void my_memset(void* dst_, uint8_t value, uint32_t size)
{
    assert(dst_ != NULL);
    uint8_t* dst = (uint8_t*)dst_;
    while(size--)
    {
        *dst++ = value;
    }
}

void* my_memcpy_v1(void* dst, const void* src, size_t len) {
    assert(dst != NULL && src != NULL);
    // 不允许内存重叠
    uint8_t* d = (uint8_t*) dst;
    const uint8_t* s = (const uint8_t*) src;
    while(len--)
    {
        *d++ = *s++; 
    }
    return dst;
}

void* my_memcpy_v2(void* dst, const void* src, size_t len) {
    assert(dst != NULL && src != NULL);

    uint8_t* d = (uint8_t*) dst;
    const uint8_t* s = (const uint8_t*) src;

    // 按 4 字节拷贝
    size_t i = 0;
    for (; i + 4 <= len; i += 4) {
        *d = *s;
        *(d + 1) = *(s + 1);
        *(d + 2) = *(s + 2);
        *(d + 3) = *(s + 3);
        d += 4;
        s += 4;
    }

    // 处理剩余字节
    while (i < len) {
        *d++ = *s++;
        i++;
    }

    return dst;
}

int main()
{
    char dst[128] = {0};
    const char* src = "abcdef";

    my_memset(dst, 0, sizeof(dst));
    my_memcpy_v1(dst, src, strlen(src) + 1);
    printf("memcpy_v1 result: %s\n", dst);

    my_memset(dst, 0, sizeof(dst));
    my_memcpy_v2(dst, src, strlen(src) + 1);
    printf("memcpy_v2 result: %s\n", dst);

    return 0;
}
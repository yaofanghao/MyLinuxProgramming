/*
 * @Author: yao fanghao
 * @Date: 2023-05-07 10:34:49
 * @LastEditTime: 2023-05-07 11:18:29
 * @LastEditors: yao fanghao
 */
#include <stdio.h>


void* memcpy_v1(void* dst, const void* src, size_t len) {
    char* d = (char*) dst;
    const char* s = (const char*) src;
    while(len--)
    {
        *d++ = *s++; 
    }
    return dst;
}

void* memcpy_v2(void* dst, const void* src, size_t len) {
    char* d = (char*) dst;
    const char* s = (const char*) src;
    
    size_t i = 0;
    for (; i + 4 < len; i += 4, d = d + 4, s = s + 4) {
        *d = *s;
        *(d + 1) = *(s + 1);
        *(d + 2) = *(s + 2);
        *(d + 3) = *(s + 3);
    }
    return dst;
}

int main()
{
    char* dst = "";
    char* src = "abcdef";



}
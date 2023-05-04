/*
 * @Author: yao fanghao
 * @Date: 2023-05-01 13:08:26
 * @LastEditTime: 2023-05-03 15:56:22
 * @LastEditors: yao fanghao
 */
#include <stdio.h>
#include <stdlib.h>

static void f1(void)
{
    puts("f1() is working");
}

static void f2(void)
{
    puts("f2() is working");
}

static void f3(void)
{
    puts("f3() is working");
}

int main()
{
    puts("begin");

    // 钩子函数的用途示例
    atexit(f1);
    atexit(f2);
    atexit(f3);

    exit(0);
}
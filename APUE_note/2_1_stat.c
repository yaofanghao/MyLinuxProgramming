/*
 * @Author: yao fanghao
 * @Date: 2023-04-23 15:35:24
 * @LastEditTime: 2023-04-23 16:07:05
 * @LastEditors: yao fanghao
 */
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// 模拟ls命令 读取文件大小
static int flen(char *fname)
{
    struct stat statres;
    if(stat(fname, &statres) < 0)
    {
        perror("stat():");
        exit(1);
    }

    return statres.st_size;
}

// 模拟ls命令 读取文件类型
static int ftype(char *fname)
{
    struct stat statres;
    if(stat(fname, &statres) < 0)
    {
        perror("stat():");
        exit(1);
    }
    
    if(S_ISREG(statres.st_mode))  // 如果读取到文件类型是常规文件
    {
        return '-';
    }
    else if(S_ISDIR(statres.st_mode))  // 如果读取到文件类型是目录
    {
        return 'd';
    }
    else if(S_ISSOCK(statres.st_mode))  // 如果读取到文件类型是socket套接字文件
    {
        return 's';
    }    
    else  // 其他情况待定
    {
        return '?';
    }
}


int main(int argc, char **argv)
{
    if(argc <2)
    {
        fprintf(stderr, "usage %s [cmd] \n", argv[0]);
        exit(1);
    }

    printf("%lld \n", (long long)flen(argv[1]));
    printf("%c \n", ftype(argv[1]));
    exit(0);
}
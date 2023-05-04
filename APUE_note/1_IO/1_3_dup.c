/*
 * @Author: yao fanghao
 * @Date: 2023-04-23 11:51:22
 * @LastEditTime: 2023-04-23 14:36:52
 * @LastEditors: yao fanghao
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FILENAME "/temp/temp"

// dup的使用 复制文件描述符
int main()
{
    int fd;
    close(1);

    fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if(fd <0 )
    {
        perror("open():");
        exit(1);        
    }

    // close(1);
    // dup(fd);
    dup2(fd, 1);  // 拷贝fd

    if(fd != 1)
    {
        close(fd);        
    }

    puts("hello!");   
    exit(0);
}
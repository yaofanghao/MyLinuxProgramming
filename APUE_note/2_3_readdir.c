/*
 * @Author: yao fanghao
 * @Date: 2023-04-24 21:36:15
 * @LastEditTime: 2023-04-24 22:05:42
 * @LastEditors: yao fanghao
 */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#define PAT "/etc/a*.conf"

// 调用readdir()遍历目录子文件
int main(int argc, char **argv)
{
    DIR *dp;
    struct dirent *cur;

    if((dp=opendir(PAT)) == NULL)
    {
        perror("opendir(): ");
        exit(1);
    }

    while(cur = readdir(dp))
    {
        // 读取、打印文件名、文件类型等信息
        puts(cur->d_name);
        puts(cur->d_type);
    }

    closedir(dp);
    exit(0);
}

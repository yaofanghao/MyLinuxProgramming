/*
 * @Author: yao fanghao
 * @Date: 2023-04-21 10:44:31
 * @LastEditTime: 2023-04-21 14:48:48
 * @LastEditors: yao fanghao
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFSIZE 1024

// 实现功能：
//     将fps文件中的内容复制到fpd中
int main(int argc, char **argv)
{
    if(argc<3)
    {
        fprintf(stderr, "usage: %s [src_file] [dst_file] \n", argv[0]);      
        exit(1);
    }

    FILE *fps;  
    FILE *fpd;  
    char ch;
    char buf[BUFSIZE];
    int count = 0; 

    fps = fopen(argv[1],"r");
    if(fps == NULL)
    {
        // 打开文件，如异常返回信息
        // 方法1 
        // fprintf(stderr, "fopen() failed, errno = %d \n", errno);  // fopen() failed, errno = 2

        // 更推荐以下两种方法，需包含头文件 <string.h>
        // 方法2 strerror(errno)
        // fprintf(stderr, "fopen() failed, %s \n", strerror(errno));  // open() failed, No such file or directory
        
        // 方法3  
        perror("fopen()");
        exit(1);
    }

    fpd = fopen(argv[2],"w");  // 如果不输入 argv[2] ，程序会输出：[fopen(): Bad address]
    if (fpd == NULL)
    {
        fclose(fps);
        perror("fopen()");
        exit(1);
    }

    printf("success open %s", argv[1]);
    
    // 方法1
    // 每次读一个字符并写入    
    // while(1)
    // {
        // ch = fgetc(fps);
        // if (ch == EOF)
        // {
        //     break;  // 读到文件末尾即退出
        // }
        // count++;
        // fputc(ch, fpd);
    // }
    
    // 方法2
    // 每次读SIZE个大小的字符串并写入
    while(fgets(buf, BUFSIZE, fps) != NULL)
    {
        fputs(buf, fpd);
        count++;
    }

    // 首先关闭目的文件，再关闭源文件
    fclose(fpd);
    fclose(fps);
    printf("success copy [%s] to [%s] and close \n", argv[1], argv[2]);
    printf("length of file is %d \n", count);
    exit(0);
}
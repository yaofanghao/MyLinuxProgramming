/*
 * @Author: yao fanghao
 * @Date: 2023-04-21 21:11:11
 * @LastEditTime: 2023-04-22 10:59:05
 * @LastEditors: yao fanghao
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

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

    int sfd, dfd;
    char buf[BUFSIZE];
    int len, ret;
	int pos; 

    sfd = open(argv[1], O_RDONLY);
    if(sfd < 0)
    {
        perror("open():");
        exit(1);
    }

    // 如果dfd存在就读写，不存在就创建并清空，文件权限为600
    dfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if(dfd <0 )
    {
        close(sfd);
        perror("open():");
        exit(1);        
    }

    // 实现对文件的读写
    while(1)
    {
        len = read(sfd, buf, BUFSIZE);
        if(len < 0)
        {
            perror("read():");
            exit(1);   
        }
        if(len == 0)
        {
            break;   
        }
        
		pos = 0;
		while(1)
		{
			ret = write(dfd, buf+pos, len);
			if(ret < 0)
			{
				perror("write():");
				exit(1);   
			}
			pos += ret;
			len -= ret;
		}		
        if(ret == 0)
        {
            break;   
        }
    }

    // 首先关闭目的文件，再关闭源文件
    close(dfd);
    close(sfd);
    printf("success copy [%s] to [%s] and close \n", argv[1], argv[2]);
    exit(0);
}

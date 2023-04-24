/*
 * @Author: yao fanghao
 * @Date: 2023-04-24 21:36:15
 * @LastEditTime: 2023-04-24 21:51:49
 * @LastEditors: yao fanghao
 */
#include <stdio.h>
#include <stdlib.h>
#include <glob.h>

#define PAT "/etc/a*.conf"

// 打印失败原因
int errfunc_(const char *epath, int eerrno)
{
    puts(epath);
    fprintf(stderr, "ERROR MSG: %s \n", strerror(eerrno));
    exit(0);    
}

// 调用glob()进行目录分析的操作
int main(int argc, char **argv)
{
    // glob函数原型:
    // int glob(const char *restrict pattern, int flags,
    //     int (*errfunc)(const char *epath, int eerrno),
    //     glob_t *restrict pglob);

    glob_t globres;
    int err;

    // err = glob(PAT, 0, errfunc_, &globres);

    err = glob(PAT, 0, NULL, &globres);
    if(err)
    {
        printf("Error code = %d \n", err);
        exit(1);
    }

    for(int i=0; i<globres.gl_pathc; i++)
    {
        puts(globres.gl_pathv[i]);
    }

    globfree(&globres);
    exit(0);
}

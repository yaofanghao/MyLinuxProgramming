#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <glob.h>
#include <string.h>

#define PATHSIZE 1024

static int64_t path_noloop(const char *path)
{
    char *pos;
    pos = strrchr(path, '/');
    if(pos == NULL)
    {
        exit(1);
    }
    if(strcmp(pos+1, ".") == 0 || strcmp(pos+1, "..") == 0)
    {
        return 0;
    }
    return 1;
}

// 模拟du命令 递归读取文件目录
static int64_t mydu(const char *path)
{
    struct stat statres;
    char nextpath[PATHSIZE];
    glob_t globres;
    int64_t su

    if(lstat(path, &statres) < 0)
    {
        perror("lstat()");
        exit(1);
    }    

    // path为非目录文件    
    if(!S_ISDIR(statres.st_mode))
    {
        return statres.st_blocks/2;
    }
    
    // path为目录文件
    strncpy(nextpath, path, PATHSIZE);
    strncat(nextpath, "/*", PATHSIZE);
    glob(nextpath, 0, NULL, &globres);

    sum = 0;
    for(int i=0; i<globres.gl_pathc; i++)
    {
        // 如果读到的目录不是.或者..
        if(path_noloop(globres.gl_pathv[i]))
        {
            sum += mydu(globres.gl_pathv[i]);            
        }
    }
    sum += statres.st_blocks;

    return sum;

    // strncpy(nextpath, path, PATHSIZE);
    // strncat(nextpath, "/*", PATHSIZE);
    // glob(nextpath, GLOBAL_APPEND, 0, NULL, &globres);
}


int main(int argc, char** argv)
{
    if(argc < 2)
    {
        fprintf(stderr, "Usage... \n");
        exit(1);
    }

    printf("%lld \n", mydu(argv[1])/2);



    exit(0);
}
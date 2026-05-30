/*
 * @Author: yao fanghao
 * @Date: 2023-05-06 16:36:57
 * @LastEditTime: 2023-05-15 16:47:33
 * @LastEditors: yao fanghao
 */
//lhq yyds
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>
#include <glob.h>
#include <string.h>

#define BUFSIZE 1024
#define DELIMS " \t\n"

extern char **environ;

static int cd(char *path){
    int ret = chdir(path);
    if (ret == -1){
        perror("chdir");
    }
    return ret;
}

static void readrc(char *name){
    FILE *fp;
    fp = fopen(name,"r+");
    //处理文件内容
    fclose(fp);
}

static void prompt()
{
    char pwd[BUFSIZE];
    char name[BUFSIZE];
    getcwd(pwd,BUFSIZE);
    getlogin_r(name,BUFSIZE);
    printf("%s %s $ ",name,pwd);
}

static int parse(char *linebuf,glob_t *globres){
    char *tok;
    int flag = 0;
    

    while (1){
        tok = strsep(&linebuf,DELIMS);
        if (tok == NULL){
            return -1;
        }else if(strcmp(tok,"cd") == 0){
            char *path = strsep(&linebuf,DELIMS);
            return cd(path);
        }else if(tok[0] == '\0'){
            continue;
        }

        glob(tok,GLOB_NOCHECK|GLOB_APPEND*flag,NULL,globres);//第一次不能append glob_argv中是随机值 GLOB_NOCHECK | (GLOB_APPEND*flag)==0 第一次不append
        flag = 1;
    }
    return 1;
}


//之后记得 将 ctrl+c 转为 stdout:\n 将ctrl+d 转为 退出+再见标语
int main()
{
    printf("This is YSHELL\n");

    pid_t pid = -1;
    char *linebuf = NULL;
    size_t lienbuf_size = 0;
    glob_t globres;
    memset(&globres, 0, sizeof(globres));

    //读取配置文件
    char *yshrc = "/home/yixingwei/.yshrc";
    readrc(yshrc);

    while(1){
        prompt();

        //获取命令
        if (getline(&linebuf,&lienbuf_size,stdin) == -1){
            printf("\nGoodbye!\n");
            break;
        }
        //解析命令
        int ret = parse(linebuf,&globres);
        
        if (ret == -1){
            // parse error
        }else if (ret == 0){//内部命令
            // already handled in parse()
        }else if (ret == 1){//外部命令
            fflush(NULL);
            pid = fork();
            if (pid < 0){
                perror("fork()");
                exit(1);
            }else if(pid == 0){
                execvp(globres.gl_pathv[0],globres.gl_pathv);
                perror("execvp()");
                exit(1);
            }
        }
        if (pid > 0){
            waitpid(pid,NULL,0);
            pid = -1;
        }
        globfree(&globres);
        memset(&globres, 0, sizeof(globres));
    } 
    
    free(linebuf);
    exit(0);
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <errno.h>
#include <string.h>

int main(int argc,char **argv)
{
    if (argc < 3){
        fprintf(stderr,"Usage: %s <uid> <command> [args...]\n", argv[0]);
        exit(1);
    }

    // 安全检查：只有 root 或拥有 CAP_SETUID 权限的进程才能执行
    if (geteuid() != 0){
        fprintf(stderr,"Error: Operation not permitted (must be root)\n");
        exit(1);
    }

    // 验证 UID 参数
    char *endptr;
    long uid = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || uid < 0 || uid > 65535){
        fprintf(stderr,"Error: Invalid UID '%s'\n", argv[1]);
        exit(1);
    }

    pid_t pid;

    pid = fork();
    if (pid == 0){
        if (setuid((uid_t)uid) < 0){
            fprintf(stderr,"Error: setuid(%ld) failed: %s\n", uid, strerror(errno));
            exit(1);
        }
        execvp(argv[2], argv+2);
        perror("execvp()");
        exit(1);

    }else if (pid < 0){
        perror("fork()");
        exit(1);
    }else {
        wait(NULL);
    }

    exit(0);
}


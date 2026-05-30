#include <stdio.h>
#include <stdlib.h>
#include <sys/syslog.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>

#define FNAME "/tmp/out"

static int daemonize(){
    int fd;
    pid_t pid;

    pid = fork();
    if (pid < 0){
        return -1;
    }
    if (pid > 0){
        exit(0);
    }

    // 子进程：创建新会话，脱离终端
    if (setsid() < 0){
        return -1;
    }

    // 第二次 fork，防止重新获取终端
    pid = fork();
    if (pid < 0){
        return -1;
    }
    if (pid > 0){
        exit(0);
    }

    // 设置文件权限掩码
    umask(0);

    // 关闭所有继承的文件描述符 / 重定向到 /dev/null
    fd = open("/dev/null", O_RDWR);
    if (fd < 0){
        return -1;
    }
    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);
    if (fd > 2){
        close(fd);
    }

    // 切换工作目录
    chdir("/");

    return 0;
}

int main()
{
    FILE* fp;

    //开启日志服务
    openlog("print i",LOG_PID,LOG_DAEMON);

    if (daemonize()){
        syslog(LOG_ERR,"init failed!");
    }else{
        syslog(LOG_INFO,"succeeded!");
    }

    fp = fopen(FNAME,"w+");
    if (fp == NULL){
        syslog(LOG_ERR,"write file failed!");
        exit(1);
    }

    syslog(LOG_INFO,"%s opened",FNAME);

    // 守护进程循环写入日志，收到 SIGTERM 信号时退出
    int i = 0;
    while(1){
        fprintf(fp,"%d\n",i);
        fflush(fp);
        syslog(LOG_DEBUG,"%d 写入",i);
        sleep(1);
        i++;
    }

    closelog();
    fclose(fp);
    exit(0);
}


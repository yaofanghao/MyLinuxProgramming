/*
 * @Author: yao fanghao
 * @Date: 2023-05-10 17:01:21
 * @LastEditTime: 2023-05-10 17:53:26
 * @LastEditors: yao fanghao
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define N 5

int main()
{
    printf("[%d] start !\n",getpid());
    fflush(NULL);

    int status;
    pid_t pid[N], res;

    // for(int i=0; i<N; i++)
    // {
    //     switch (fork())
    //     {
    //         case -1:  // error
    //             perror("fork()");
    //         case 0:  // child      
    //             printf("\n");  
    //             printf("[%d] child \n", getpid());    
    //             printf("[%d] child's parent \n", getppid());  
    //             exit(200+i);
    //         default:  // parent
    //             while(waitpid(-1, &status, 0)>0)
    //             {
    //                 if(WIFEXITED(status))
    //                     printf("[%d] child exit staus is %d\n", getpid(), WEXITSTATUS(status));
    //             }
    //             printf("[%d] parent \n", getpid()); 
    //     }rm w
    // }
   
    for(int i=0; i<N; i++)
    {
        if((pid[i]=fork())==0)
        {
            printf("\n");  
            printf("[%d] child \n", getpid());    
            printf("[%d] child's parent \n", getppid());  
            exit(200+i);
        }
    }

    int j=0;
    while((res=waitpid(pid[j++], &status, 0))>0)
    {
        // sleep(2);
        if(WIFEXITED(status))
            printf("[%d] child exit staus is %d\n", res, WEXITSTATUS(status));
    }

    printf("end.\n");
    exit(2);    

}
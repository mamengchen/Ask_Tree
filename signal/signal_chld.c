//这是个用信号避免僵尸进程的demo
//

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

void out(int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d out %d\n", getpid(), i);
        sleep(1);
    }
}


void sig_handler(int signo)
{
    printf("child process deaded, signo: %d\n", signo);
    //当父进程捕获到SIGCHLD信号后要调用wait函数
    //去回收子进程，否则子进程会成为僵尸进程.
    wait(0);
}

int main(void)
{
    if (signal(SIGCHLD, sig_handler) == SIG_ERR) 
    {
        perror("signal sigchld error");
    }
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork error");
        exit(1);
    } else if (pid > 0){
        //parent process
        out(100);
    } else {
        //child process
        out(20);
    }
    return 0;
}

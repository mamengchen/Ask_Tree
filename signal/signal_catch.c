//进程信号的demo
//void (*signal(int signo, void (*func)(int)))(int);
//返回：若成功则返回先前的信号处理函数指针，出错则返回SIG_ERR．
//功能：向内核登记信号处理函数

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

//定义信号处理函数
//signo:进程捕获的信号
void sig_handler(int signo)
{
    printf("%d, %d occured\n", getpid(), signo);
}

int main(void)
{
    //向内核登记信号处理函数以及信号值
    if (signal(SIGTSTP, sig_handler) == SIG_ERR)
    {
        perror("signal sigtstp error");
    }
    if (signal(SIGINT, sig_handler) == SIG_ERR)
    {
        perror("signal sigint error");
    }

    //原本这两个信号是程序运行起来是忽略掉的，登记一下就可以不忽略
    if (signal(SIGUSR1, sig_handler) == SIG_ERR)
    {
        perror("signal sigusr1 error");
    }
    if (signal(SIGUSR2, sig_handler) == SIG_ERR)
    {
        perror("signal sigusr2 error");
    }
    //忽略信号
    //if (signal(SIGINT, SIG_IGN) == SIG_ERR)
    //{
    //    perror("signal sigint error");
    //}
    //
    //SIGKILL和SIGSTOP永远不能忽略或者捕获

    int i = 0;
    while (i < 50)
    {
        printf("%d out %d\n", getpid(), i++);
        if (i == 10)
        {
            kill(gitpid(), SIGKILL);
        }
        sleep(1);
    }

    //向进程自己发送SIGUSR1和SIGUSR2信号
    raise(SIGUSR1);
    kill(getpid(), SIGUSR2);


    return 0;
}

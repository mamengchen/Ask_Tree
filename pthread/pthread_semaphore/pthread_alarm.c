#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int signo)
{
    printf("在函数 sig_handler 中的线程ID: %lx\n", pthread_self());
    if (signo == SIGALRM)
    {
        printf("超时....\n");
    }
    alarm(2);
}

void *th_fn(void *arg)
{
    if (signal(SIGALRM, sig_handler) == SIG_ERR)
    {
        perror("信号sigalrm　失效");
    }

    //在子线程中设置定时器
    alarm(2);

    int i;
    for (i = 1; i <= 100; i++)
    {
        printf("(%lx) i: %d\n", pthread_self(), i);
        sleep(1);
    }
    return (void *)0; //pthread_exit((void *)0);
}

void *th_fn2(void *arg)
{
    pthread_t th1 = (pthread_t)arg;

    int i;
    for (i = 1; i <= 15; ++i)
    {
        if (i == 5)
        {
            //终止线程１的运行
            pthread_cancel(th1);
            alarm(0);
        }
        printf("(%lx) i : %d\n", pthread_self(), i);
        sleep(1);
    }
    return (void *)0;
}

int main(void)
{
    int err;
    pthread_t th, th2;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    if ((err = pthread_create(&th, &attr, th_fn, (void *)0)) != 0)
    {
        perror("线程创建失败");
    }
    
    if ((err = pthread_create(&th2, &attr, th_fn2, (void *)th)) != 0)
    {
        perror("线程创建失败");
    }

    sigset_t    set;
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    //对主控线程屏蔽SIGALRM的信号
    pthread_sigmask(SIG_SETMASK, &set, NULL);

    while (1)
    {
        printf("主控线程(%lx) is running.......\n", pthread_self());
        sleep(10);
    }
    printf("主控线程失效\n");


    return 0;
}

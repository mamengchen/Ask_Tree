//这是一个线程计算，一个线程获得结果，计算没有完毕，获得结果的线程等待:这就是同步，是要一种次序
//利用线程信号量（更改条件变量）../pthread_cal.c

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>


typedef struct {
    int res;
    sem_t sem;
}Result;

//计算并将结果放置Result中的线程运行函数
void* set_fn(void *arg)
{
    int i = 1, sum = 0;
    for (; i <= 100; i++)
    {
        sum += i;
    }
    Result *r = (Result *)arg;
    r->res = sum;
    
    //V(1)操作
    sem_post(&r->sem);

    return (void *)0;
}

//从Result中获取资源
void* get_fn(void *arg)
{
    Result *r = (Result *)arg;
    
    //p(1)操作
    sem_wait(&r->sem);

    //获取计算结果
    int res = r->res;
    printf("0x%lx 获取的Result的结果是 %d\n", pthread_self(), res);
    return (void *)0;
}

int main(void)
{
    int err;
    pthread_t cal, get;
    Result r;

    sem_init(&r.sem, 0 ,0);
    //启动获取结果的线程
    if((err = pthread_create(&get, NULL, get_fn, (void *)&r)) != 0)
    {
        perror("pthread get error");
    }
    
    //启动计算结果的线程
    if((err = pthread_create(&cal, NULL, set_fn, (void *)&r)) != 0)
    {
        perror("pthread set error");
    }

    pthread_join(cal, NULL);
    pthread_join(get, NULL);

    sem_destroy(&r.sem);
    return 0;
}

//这是一个线程计算，多个线程获得结果，计算没有完毕，获得结果的线程等待:这就是同步，是要一种次序

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct {
    int res;
    int counter;  //用户统计获取结果线程
    pthread_cond_t cond;    //条件变量
    pthread_mutex_t mutex;  //互斥锁
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

    //对共享的资源进行枷锁
    pthread_mutex_lock(&r->mutex);
    //判断获取结果的线程是否达到指定的数量
    while (r->counter < 2)
    {
        pthread_mutex_unlock(&r->mutex); //如果不在循环中释放互斥锁，另一个线程没办法改变is_wait
        usleep(100);
        pthread_mutex_lock(&r->mutex);
    }
    pthread_mutex_unlock(&r->mutex);
    
    //通知唤醒等待的那个获取结果的线程
    pthread_cond_broadcast(&r->cond);

    return (void *)0;
}

//从Result中获取资源
void* get_fn(void *arg)
{
    Result *r = (Result *)arg;
    
    //对两个线程共享的判断条件进行保护（加锁）
    //两个线程对判断条件操作是互斥的
    pthread_mutex_lock(&r->mutex);
    r->counter++;

    //获取结果的线程进入等待
    pthread_cond_wait(&r->cond, &r->mutex);
    //唤醒后解锁
    pthread_mutex_unlock(&r->mutex);

    //获取计算结果
    int res = r->res;
    printf("0x%lx 获取的Result的结果是 %d\n", pthread_self(), res);
    return (void *)0;
}

int main(void)
{
    int err;
    pthread_t cal, get1, get2;
    Result r;
    r.counter = 0;
    pthread_cond_init(&r.cond, NULL);
    pthread_mutex_init(&r.mutex, NULL);

    //启动获取结果的线程
    if((err = pthread_create(&get1, NULL, get_fn, (void *)&r)) != 0)
    {
        perror("pthread get error");
    }
    
    if((err = pthread_create(&get2, NULL, get_fn, (void *)&r)) != 0)
    {
        perror("pthread get error");
    }
    //启动计算结果的线程
    if((err = pthread_create(&cal, NULL, set_fn, (void *)&r)) != 0)
    {
        perror("pthread set error");
    }

    pthread_join(cal, NULL);
    pthread_join(get1, NULL);
    pthread_join(get2, NULL);

    pthread_cond_destroy(&r.cond);
    pthread_mutex_destroy(&r.mutex);
    return 0;
}

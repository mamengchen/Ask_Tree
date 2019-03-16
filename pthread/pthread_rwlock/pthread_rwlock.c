//　线程使用互斥锁缺乏读并发性
//　当读操作较多，写操作较少时，可使用读写锁提高线程读并发性
//  读写锁类型：pthread_rwlock_t


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//定义读写锁
pthread_rwlock_t rwlock;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("-usage:%s [r|w] [r|w]\n", argv[0]);
    }

    //初始化读写锁
    pthread_rwlock_init(&rwlock, NULL);
    if (!strcmp("r", argv[1]))
    {
        //加读锁
        if (pthread_rwlock_rdlock(&rwlock) != 0)
        {
            printf("first read lock failure\n");
        } else {
            printf("first read lock success\n");
        }
    } else if (!strcmp("w", argv[1]))
    {
        //加写锁
        if (pthread_rwlock_wrlock(&rwlock) != 0)
        {
            printf("first write lock failure\n");
        } else {
            printf("first write lock success\n");
        }
    }
    
    if (!strcmp("r", argv[2]))
    {
        //加读锁
        if (pthread_rwlock_rdlock(&rwlock) != 0)
        {
            printf("second read lock failure\n");
        } else {
            printf("second read lock success\n");
        }
    } else if (!strcmp("w", argv[2]))
    {
        //加写锁
        if (pthread_rwlock_wrlock(&rwlock) != 0)
        {
            printf("second write lock failure\n");
        } else {
            printf("second write lock success\n");
        }
    }

    pthread_rwlock_unlock(&rwlock);
    pthread_rwlock_unlock(&rwlock);
    
    return 0;
}

//这是一个哲学家用餐问题的
//描述：有五个哲学家，他们生活方式就是思考和吃饭，他们用一张圆形桌子，分别坐在五张椅子上
//．在这个圆形桌子上有五个筷子，分别在他们座位的左边，右边有一个，共五根筷子
//
//约束条件：
//１．只有拿到两只筷子时，哲学家才能吃饭．
//２．如果筷子已经被别人拿走，则必须等别人吃完之后才能拿到筷子．
//３．任一哲学家在自己未拿到两只筷子吃饭前，不会放到手中拿到的筷子．
//
//这类问题所要告诉我们的是如何实现高并发？
//就是使用多线程，在高并发问题中多线程的作用就是充分利用计算机资源，使计算机的资源在每一时刻都能达到最大的利用率
//，但是多线程对临界资源共享的，所以我们需要引入锁，对临界资源进行保护．但是锁自身也是临界资源，这样就会存在死锁
//（死锁：一个人拿了一个锁，但是他需要两个锁才能运行，但是另一个锁在别人手里）
//
//（防止：当第ｉ个哲学家将左右筷子都拿到了才允许其他哲学家拿筷子）


//第三种方案：利用率最高，至多只允许四位哲学家同时区拿左筷子，最终能保证至少有一位哲学家能进餐
//，并在用完释放两只筷子供他人使用．此方法能使资源得到有效的利用．
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

//设置５种信号量，有５种不同类型的资源，每一种有１个，这样便于理解，因为每个哲学家需要的资源不同
sem_t chopsticks[N];
sem_t m;//最多允许有４个哲学家去拿筷子
//定义互斥锁
pthread_mutex_t mutex;

int philosophers[N] = {0, 1, 2, 3, 4};//代表五个哲学家的编号

void delay(int len)
{
    int i = rand() % len;
    int x;
    while (i > 0)
    {
        x = rand() % len;
        while (x > 0)
        {
            x--;
        }
        i--;
    }
}

void *philosopher(void *arg)
{
    int i = *(int *)arg;
    int left = i; //左筷子的编号和哲学家的编号相同
    int right = (i+1)%N;    //右筷子的编号为哲学家编号＋１
    while (1) 
    {
        printf("哲学家 %d 正在思考问题\n", i);
        delay(60000);

        printf("哲学家 %d 饿了\n", i);
        //如果前４个哲学家同时拿起左筷子，第五个不能同时拿起左筷子，保证至少有一位能吃饭饭
        sem_wait(&m);
        sem_wait(&chopsticks[left]);
        printf("哲学家 %d 拿起了 %d 号筷子，现在只有一个筷子，不能进餐\n", i, left);
        sem_wait(&chopsticks[right]);
        printf("哲学家 %d 拿起了 %d 号筷子，现在有两支筷子，开始进餐\n", i, right);

        delay(60000);
        sem_post(&chopsticks[left]);
        printf("哲学家 %d 放下了 %d 号筷子\n", i, left);

        sem_post(&m);
        sem_post(&chopsticks[right]);
        printf("哲学家 %d 放下了 %d 号筷子\n", i, right);
    }
    return (void *)0;
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    pthread_t philo[N];

    //信号量初始化
    for (int i = 0; i < N; i++)
    {
        sem_init(&chopsticks[i], 0, 1);
    }
    sem_init(&m, 0, 4);

    //创建线程
    for (int i = 0; i < N; i++)
    {
        pthread_create(&philo[i], NULL, philosopher, &philosophers[i]);
    }

    //挂起线程
    for (int i = 0; i < N; i++)
    {
        pthread_join(philo[i], NULL);
    }

    //销毁信号量
    for (int i = 0; i < N; i++)
    {
        sem_destroy(&chopsticks[i]);
    }
    sem_destroy(&m);
    return 0;
}

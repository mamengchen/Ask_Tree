#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    int code;
    double balance;
    //互斥锁用来锁定一个用户，否则可能出现一把锁区锁几百
    //账号，导致并发性降低
    //定义读写锁
    //pthread_rwlock_t rwlock;
    
    //定义线程信号量
    sem_t sem;

}Account;


//创建账号
extern Account* create_account(int code, double balance);
//销毁账号
extern void destroy_account(Account *a);
//取款
extern double withdraw(Account *a, double amt);
//存款
extern double deposit(Account *a, double amt);
//查看账号余额
extern double get_balance(Account *a);

#endif

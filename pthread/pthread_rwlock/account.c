#include "account.h"
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

//创建账号
Account* create_account(int code, double balance)
{
    Account *a = (Account*)malloc(sizeof(Account));
    assert(a != NULL);
    a->code = code;
    a->balance = balance;

    //对读写锁进行初始化
    pthread_rwlock_init(&a->rwlock, NULL);
    
    return a;
}
//销毁账号
void destroy_account(Account *a)
{
    assert(a != NULL);

    //销毁读写锁
    pthread_rwlock_destroy(&a->rwlock);
    free(a);
}
//取款
double withdraw(Account *a, double amt)
{
    assert(a != NULL);
 
    //对共享资源操作的临界区
    //加写锁
    pthread_rwlock_wrlock(&a->rwlock);

    if (amt < 0 || amt > a->balance)
    {
        //释放读写锁
        pthread_rwlock_unlock(&a->rwlock);
        return 0.0;
    }
    double balance = a->balance;
    sleep(1);
    balance -= amt;
    a->balance = balance;
    //释放读写锁
    pthread_rwlock_unlock(&a->rwlock);
    
    return amt;
}
//存款
double deposit(Account *a, double amt)
{
    assert(a != NULL);

    //加写锁
    pthread_rwlock_init(&a->rwlock, NULL);

    if (amt < 0)
    {
        //释放写锁
        pthread_rwlock_unlock(&a->rwlock);
        return 0.0;
    }
    double balance = a->balance;
    sleep(1);
    balance += amt;
    a->balance = balance;
    
    //释放写锁
    pthread_rwlock_unlock(&a->rwlock);
    return amt;
}
//查看账号余额
double get_balance(Account *a)
{
    assert(a != NULL);

    //加读锁
    pthread_rwlock_rdlock(&a->rwlock);
    double balance = a->balance;
    
    pthread_rwlock_unlock(&a->rwlock);
    return balance;
}


#include "account.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct{
    char name[20];
    Account *account;
    double amt;
}OperArg;

void* withdraw_th(void* arg)
{
    OperArg *oa = (OperArg*)arg;
    double amt = withdraw(oa->account, oa->amt);
    printf("%8s(0x%lx) withdraw %f from account %d\n",
           oa->name, pthread_self(), amt, oa->account->code);
    
    return (void*)0;
}

void* deposit_th(void* arg)
{
    
    return (void*)0;
}

void* balance_th(void* arg)
{
    return (void *)0;
}

int main()
{
    int err;
    pthread_t b1,b2;
    Account *a = create_account(10001, 10000);
    OperArg o1, o2;
    strcpy(o1.name, "b1");
    o1.account = a;
    o1.amt = 10000;
    
    strcpy(o2.name, "b2");
    o2.account = a;
    o2.amt = 10000;
    
    if ((err = pthread_create(&b1, NULL, withdraw_th, (void*)&o1)) != 0)
    {
        perror("b1 error");
    }
    if ((err = pthread_create(&b2, NULL, withdraw_th, (void*)&o2)) != 0)
    {
        perror("b2 error");
    }

    pthread_join(b1, NULL);
    pthread_join(b2, NULL);

    printf("account balance: %f\n", get_balance(a));
    destroy_account(a);

    return 0;
}

//这是一个单例模式的demo,单例模式意思就是一个工程只有一个实例化

#include <iostream>
#include <stdio.h>

using namespace std;

class Singleton {
private:
    Singleton()
    {
        m_singer = NULL;
        cout << "构造一个单例对象" << endl;
    }
public:
    static Singleton* getInit() //懒汉模式：会有线程安全问题（在对象来的时候开始创建）　　
    {
        if (m_singer == NULL)
        {
            m_singer = new Singleton;
        }
        return m_singer;
    }
public:
    static Singleton* m_singer;
};

Singleton *Singleton::m_singer = NULL;
//Singleton *Singleton::m_singer = new Singleton; //饿汉模式（程序运行即创建）
int main()
{
    Singleton* p = Singleton::getInit();
    Singleton* q = Singleton::getInit();
    printf("p:%x q:%x\n",p,q );
    return 0;
}

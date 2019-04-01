#include <iostream>
#include <pthread>
#include <mutex>
using namespace std;

class Singleton {
public:
    static Singleton GetInstance {

    }

private:
    Singleton()
    {
        m_test = new Singleton();
        cout << "构造一个对象" << endl;
    }
    Singleton* m_test;
};
int main()
{

    return 0;
}

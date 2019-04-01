////回避多线程的安全问题
//#include <stdio.h>
//#include <iostream>
//#include <map>
//using namespace std;
//
//class Singleton;
//static std::map<string, Singleton*> myMap = std::map<string, Singleton*>();
//
////懒汉模式-延迟加载
//class Singleton {
//
//private:
//	Singleton()
//	{
//		my_singleton = NULL;
//		cout << "单例模式正在创建" << endl;
//	}
//
//public:
//	static Singleton* getInstance()
//	{
//		if (myMap.find(DEFAULT_KEY) != myMap.end())
//		{
//			return myMap.find(DEFAULT_KEY)->second;
//		}
//
//		if (my_singleton == NULL)
//		{
//			my_singleton = new Singleton;
//			myMap[DEFAULT_KEY] = my_singleton;
//		}
//		return my_singleton;
//	}
//private:
//	static Singleton* my_singleton;
//	static string DEFAULT_KEY;
//};
//
//Singleton* Singleton::my_singleton = NULL;
//string Singleton::DEFAULT_KEY = "One";
//
//int main()
//{
//	Singleton* p1 = Singleton::getInstance();
//	Singleton* p2 = Singleton::getInstance();
//	printf("p1~s addr = %x,  p2~s addr = %x\n", p1, p2);
//	system("pause");
//	return 0;
//}
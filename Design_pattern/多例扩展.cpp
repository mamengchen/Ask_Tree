////这是一个多例扩展
//#include <string>
//#include <stdio.h>
//#include <map>
//#include <iostream>
//using namespace std;
//
////缓存的实例个数
//const static int NUM_MAX = 5;
//class Singleton;
//static std::map<int, Singleton*> myMap = std::map<int, Singleton*>();
//
//class Singleton {
//private:
//	Singleton()
//	{
//		my_singleton = NULL;
//		cout << "多例模式正在生产\n" << endl;
//	}
//	
//public:
//	static Singleton* getInsetance()
//	{
//		my_singleton = myMap[my_InstanceCount];
//		if (my_singleton == NULL)
//		{
//			my_singleton = new Singleton;
//			myMap[my_InstanceCount] = my_singleton;
//		}
//		my_InstanceCount++;
//		if (my_InstanceCount > NUM_MAX)
//		{
//			my_InstanceCount = 1;
//		}
//		return my_singleton;
//	}
//private:
//	static Singleton* my_singleton;
//	static int my_InstanceCount;	//存放实例的个数
//};
//
//Singleton* Singleton::my_singleton = NULL;
//int Singleton::my_InstanceCount = 1;	
//
//int main()
//{
//	Singleton* p1 = Singleton::getInsetance();
//	Singleton* p2 = Singleton::getInsetance();
//	Singleton* p3 = Singleton::getInsetance();
//	Singleton* p4 = Singleton::getInsetance();
//	Singleton* p5 = Singleton::getInsetance();
//	printf("p1 = %x\n", p1);
//	printf("p2 = %x\n", p2);
//	printf("p3 = %x\n", p3);
//	printf("p4 = %x\n", p4);
//	printf("p5 = %x\n", p5);
//	Singleton* p6 = Singleton::getInsetance();
//	Singleton* p7 = Singleton::getInsetance();
//	Singleton* p8 = Singleton::getInsetance();
//	Singleton* p9 = Singleton::getInsetance();
//	Singleton* p10 = Singleton::getInsetance();
//	printf("p6 = %x\n", p6);
//	printf("p7 = %x\n", p7);
//	printf("p8 = %x\n", p8);
//	printf("p9 = %x\n", p9);
//	printf("p10 = %x\n", p10);
//	system("pause");
//	return 0;
//}
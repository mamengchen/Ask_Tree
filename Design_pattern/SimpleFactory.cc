#include <iostream>
#include <string>
#include "DynOBJ.h"


#define REG_CLASS(class_name) \
class class_name##Helper { \
public: \
    ImpleTwoHelper() { \
        CobJectFactory::registerClass(#class_name, class_name##Helper::createObjFunc); \
    } \
    static void* createObjFunc() { \
        return new class_name; \
    } \
}; \
class_name##Helper class_name##helper;

using namespace std;


//对象间结构
//简单工厂的定义
//１>：提供一个创建对象实例的功能，而无需关心其具体实现．被创建的类型可以是接口，抽象类，也可以是具体的类．
//下面代码不好地方是要给用户暴露了Imp1()
//class Api {
//public:
//    virtual void test(string s) = 0;
//protected:
//    Api(){}//屏蔽构造函数，体现接口
//};
//
//class Imp1:public Api {
//public:
//    void test(string s) {
//        cout << "Imp1::Api is go back: " << s << endl; 
//    }
//};


class Api {
public:
    virtual void test(string s) = 0;
protected:
    Api(){}//屏蔽构造函数，体现接口
};

class ImpleOne:public Api {
public:
    void test(string s) {
        cout << "ImpleOne::Api is go back: " << s << endl; 
    }
};

class ImpleTwo:public Api {
public:
    void test(string s) {
        cout << "ImpleTwo::Api is go back: " << s << endl; 
    }
};

class Factory {
public:
    static Api* createApi(int type)
    {
        Api* pApi = nullptr;
        if (type == 1)
        {
            pApi = new ImpleOne();
        }

        if (type == 2)
        {
            pApi = new ImpleTwo();
        }
        return pApi;
    }
};

//class ImpleTwoHelper {
//public:
//    ImpleTwoHelper() {
//        CobJectFactory::registerClass("ImpleTwo", ImpleTwoHelper::createObjFunc);
//    }
//
//    static void* createObjFunc() {
//        return new ImpleTwo;
//    }
//};

REG_CLASS(ImpleTwo)
//测试用的客户端


class AutoFactory {
public:
    static Api* createApi()
    {
        Api* pApi = nullptr;
        pApi = static_cast<Api*>(CobJectFactory::creatObject("ImpleTwo"));
        return pApi;
    }
};


int main(void) {
    //Api* pApi = new Impl();
    //pApi->test("测试运行");

    /*
     * 使用传入参数１，可以实现从数据库读入的功能
     * 传入参数２，可以实现从文本文件读入的功能
     * 实现了客户端调用和impleOne, impleTwo的解耦合
     */
    
    //Api* pApi = Factory::createApi(1);//这里还是知道工厂细节的
    //pApi->test("现在是使用简单工厂方法重构");
    //Api* pApi = Factory::createApi(2);
    //pApi->test("现在是使用简单工厂方法重构");

    //问题的需求：
    //static Api* createApi() {
    //return new ImpleOne();//动态的实现impleone,或impletwo
    //}
    
    /* 
    ImpleTwo* pTwo = static_cast<ImpleTwo*>(ImpleTwoHelper::createObjFunc());
    pTwo->test("测试动态创建");
    */

    /*
    ImpleTwo* pTwo = static_cast<ImpleTwo*>(CobJectFactory::creatObject("ImpleTwo"));
    pTwo->test("RegClass");
    */

    Api* pApi = AutoFactory::createApi();
    pApi->test("＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊");
    return 0;
}

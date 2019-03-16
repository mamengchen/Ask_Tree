#include <iostream>
#include <stdlib.h>

class Shape {
public:
    Shape()
    {
        std::cout << "Shape::Shape()" << std::endl;
    }
    virtual double calcArea()
    {
        std::cout << "Shape::calcArea()" << std::endl;
        return 0.0;
    }
        
    ~Shape()
    {
        std::cout << "Shape::~Shape()" << std::endl;
    }
};

class Circle : public Shape
{
public:
    Circle(double r)
        :_r(r)
    {}
    
    ~Circle()
    {
        std::cout << "Circle::~Circle" << std::endl;
    }
    virtual double calcArea()
    {
        std::cout << "Circle::calcArea()" << std::endl;
        std::cout << _r*_r*3.14 << std::endl;
        return 3.15*_r*_r;
    }
protected:
    double _r;
};

class Rect : public Shape
{
public:
    Rect(double wideth, double longth)
        :_w(wideth),
        _l(longth)
    {}

    ~Rect()
    {
        std::cout << "Rect::~Rect" << std::endl;
    }

    virtual double calcArea()
    {
        std::cout << "Rect::calcArea" << std::endl;
        std::cout << _w*_l << std::endl;
        return _w*_l;
    }
protected:
    double _w;
    double _l;
};

int main(void)
{
    //这里如果那两个派生类指针就是可以实现访问不同的派生
    //的函数
    Shape* p = new Rect(3.0, 6.0);
    Shape* q = new Circle(5.0);
    p->calcArea();
    q->calcArea();
    
    delete p,q;
    //销毁的是基类的析构函数，不会调用派生类的析构函数
    //如果有资源的释放的析构函数，则需要定义为虚析构函数
    return 0;
}

//virtual不能修饰的几种函数
//1.普通全局函数不能是虚函数（编译错误）
//2.不能修饰静态成员函数(编译错误)
//3.不能修饰inline函数（这样会使inline函数变成虚函数）
//4.构造函数不能为虚函数(编译错误)

//派生类在对虚函数重写时候，派生类的虚构函数会把基类的析构函数给覆盖了
//重载和重写的区别：
//（１）范围区别：重写和被重写的函数在不同的类中，重载和被重载的函数在同一类中．
//（２）参数区别：重写与被重写的函数参数列表一定相同，重载和被重载的函数参数列表一定不同
//（３）virtual的区别：重写的基类必须要有virtual修饰, 重载函数和被重载函数可以被virtual修饰
//隐藏和重写，重载的区别：
//（１）与重载范围不同：隐藏函数和被隐藏函数在不同类中．
//（２）参数的区别：隐藏函数和被隐藏函数参数列表可以相同，也可以不同，但函数名一定相同；
//当参数不同时，无论基类中的函数是否被virtual修饰，基类函数都是被隐藏，而不是被重写．
//
//纯虚函数中函数需要在定义时候后面加0, 例如：virtual 返回值类型　函数名（）＝0;
//含有纯虚函数的类叫做抽象类，抽象类不能被实例化，仅含有纯虚函数的类称为接口类（无数据成员，只有虚成员方法）
//
//RTTI(运行时参数识别) typeid
//这个函数就是运行时参数识别的demo
void doSomething (Flyable* obj)
{
    obj->takeoff();
    std::cout << typeid(*obj),name() << std::endl;
    if (typeid(*obj) == typeid(Bird))
    {
        Bird* bird = dynamic_cast<Bird *>(obj);
        bird->foraging();
    }
    obj->land();
}
//dynamic_case注意事项：
//（１）只能应用于指针和引用的转换
//（２）要转换的类型中必须包含虚函数
//（３）转换成功返回子类的地址，失败返回NULL
//typeid注意事项：
//（１）type_id返回一个type_info对象的引用
//（２）如果想通过基类的指针获得派生类的数据类型．基类必须带有虚函数
//（３）只能获取对象的实际类型，也就是说只能判断是基类还是派生类，不能判断是基类的指针还是派生类指针


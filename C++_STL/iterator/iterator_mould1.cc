#include <iostream>
#include <iterator>
using namespace std;

class A
{
    typedef int MYINT;//内部类型
    using MYFLOAT = float;
};


int main()
{
    //A::MYINT a = 100;
    //定义一个迭代器对象
    iterator<input_iterator_tag, int> it;
    
    //iterator_category代表迭代器类别类型
    iterator<input_iterator_tag, int>::iterator_category;
    cout << typeid(iterator<input_iterator_tag, int>::iterator_category).name() << endl;
    
    //迭代器指向元素类型
    iterator<input_iterator_tag, int>::value_type;
    cout << typeid(iterator<input_iterator_tag, int>::value_type).name() << endl;
    
    //迭代器指向元素指针的类型
    iterator<input_iterator_tag, int>::pointer;
    cout << typeid(iterator<input_iterator_tag, int>::value_type).name() << endl;

    //迭代器指向元素的引用类型
    iterator<input_iterator_tag, int>::reference;
    cout << typeid(iterator<input_iterator_tag, int>::reference).name() << endl;

    //迭代器指向元素的指针类型，相减得到的差值类型
    iterator<input_iterator_tag, int>::difference_type;
    cout << typeid(iterator<input_iterator_tag, int>::difference_type).name() << endl;

    iterator<input_iterator_tag, int>::value_type a = 100;
    iterator<input_iterator_tag, int>::pointer pa = &a;
    iterator<input_iterator_tag, int>::reference b = a;

    cout << "a: " << a << endl;
    b = 200;
    cout << "b: " << b << endl;
    cout << "*pa: " << *pa << endl;
    return 0;
}


#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
};
    
ostream& operator<<(ostream& _cout, const Node &node)
{
    _cout << node.data;
    return _cout;
}

//考虑设计一个中间类,让它支持operator++，实际实现是链表的p = p->next;
//链表的迭代器
class list_iterator
{
public:
    list_iterator(Node *p):_p(p)
    {}

    list_iterator& operator++()
    {
        //链表的真正操作
        _p = _p->next;
        return *this;
    }

    bool operator!=(const list_iterator &it)
    {
        return _p != it._p;
    }

    Node& operator*()
    {
        return *_p;
    }
    Node *_p;
};



template<class T>
void print(T begin, T end)
{
    for (T p = begin; p != end; ++p)
    {
        cout << *p << " ";
    }
    cout << endl;
}


int main()
{
    Node n1;
    n1.data = 11;
    Node n2;
    n2.data = 22;
    Node n3;
    n3.data = 33;
    Node n4;
    n4.data = 44;
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = nullptr;

    list_iterator begin(&n1);
    list_iterator end(n4.next);
    print<list_iterator>(begin, end);
    return 0;
}

//迭代器的优势
//１．迭代器统一了对数据结构（容器）的遍历方式．
//２．迭代器隐藏数据结构（容器）遍历的细节，使用迭代器可以避免一些误操作，更加安全.
//３．迭代器搭起STL算法和STL容器之间的桥梁
//
//STL中的五种迭代器
//１．输入迭代器
//２．输出迭代器
//３．前向迭代器
//４．双向迭代器
//５．随机访问迭代器；

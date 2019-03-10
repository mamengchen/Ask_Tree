#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>

using namespace std;

template<typename Item>
class MaxHeap{
private:
    Item* data;
    int _count;
    int _capacity;

    void shiftup(int k)
    {
        while( k > 1 && data[k/2] < data[k])
        {
            swap(data[k/2], data[k]);
            k /= 2;
        }
    }

    void shiftDown(int k)
    {
        while( 2*k <= _count)
        {
            int j = 2*k; //在此轮循环中,data[k]和data[j]交换位置
            if ((j + 1) <= _count && data[j+1] > data[j])
            {
                j += 1;
            }
            if (data[k] >= data[j])
            {
                break;
            }
            swap(data[k], data[j]);
            k = j;
        }
    }

public:
    MaxHeap(int capacity)
    {
        data = new Item[capacity + 1];
        _count = 0;
        this->_capacity = capacity;
    }

    MaxHeap(Item arr[], int n)
    {
        data = new Item[n+1];
        _capacity = n;
        for (int i = 0; i < n; i++)
        {
            data[i+1] = arr[i];
        }
        _count = n;
        for (int i = _count/2; i >= 1; i--)
        {
            shiftDown(i);
        }
    }
    int size()
    {
        return _count;
    }

    bool isEmpty()
    {
        return _count == 0;
    }

    void insert(Item item)
    {
        assert(_count + 1 <= _capacity);
        /*
        if ((_count + 1) >= _capacity)
        {
            Item* New_data = new Item[_capacity*2 + 1];
            for (int i = 0; i < _capacity, i++)
            {
                New_data[i] = data[i];
            }
            _capacity = _capacity*2 + 1;
            data = New_data;
        }
        */
        data[_count + 1] = item;
        _count++;
        shiftup(_count);
    }

    void print()
    {
        for (int i = 0; i < _count; i++)
        {
            cout << data[i+1] << endl;
        }
    }

    Item extractMax()
    {
        assert(_count > 0);

        Item ret = data[1];
        
        swap(data[1], data[_count]);
        _count--;
        shiftDown(1);

        return ret;
    }

    ~MaxHeap()
    {
        delete [] data;
    }
};

int main()
{
    MaxHeap<int> maxheap = MaxHeap<int>(100);
    cout<<maxheap.size()<<endl;

    srand(time(NULL));
    for (int i = 0; i < 15; i++)
    {
        maxheap.insert(rand()%100);
    }
    maxheap.print();
    while (!maxheap.isEmpty())
    {
        cout << maxheap.extractMax() << " ";
    }
    cout << endl;
    return 0;
}


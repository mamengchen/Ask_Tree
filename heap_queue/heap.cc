#include <iostream>
#include "heap_merge.cc"
using namespace std;

template<typename T>
void heapSort1(T arr[], int n)
{
    MaxHeap<T> maxheap = MaxHeap<T>(n);
    for (int i = 0; i < n; i++)
    {
        maxheap.insert(arr[i]);
    }
    for (int i = n-1; i >= 0; i--)
    {
        arr[i] = maxheap.extractMax();
    }
}

//原地堆排序

template<typename T>
void _shiftDown(T arr[], int n, int k)
{
    while (2*k+1 < n)
    {
        int j = 2*k+1; //在次轮循环中，arr[k]和arr[j]交换位置
        if (j+1 < n && arr[j+1] > arr[j])
        {
            j += 1;
        }
        if (arr[k] >= arr[j])
        {
            break;
        }
        swap(arr[k], arr[j]);
        k = j;
    }
}
    
    
template<typename T>
void heapSort(T arr[], int n)
{
    //heapify
    for (int i = (n-1)/2; i >= 0; i--)
    {
        _shiftDown(arr, n, i);
    }

    for (int i = n-1 ; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        _shiftDown(arr, i, 0);
    }
}

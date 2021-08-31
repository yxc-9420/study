#ifndef CARRAY_H
#define CARRAY_H
#include<iostream>
#include<memory>
#include<vector>
using namespace std;
class CArray
{
private:
    int *arr;
    int length;
public:
    CArray():length(0){};
    explicit CArray(int arr[],int length):arr(arr),length(length){};
    void bubblesort();//冒泡
    void quicksort();//快速
    void selectsort();//选择
    void insertsort();//插入
    void heapsort();//堆
    void countsort();//计数
    void mergesort();//归并
    void bucketsort();//桶
    void radixsort();//基数
    void shellsort();//希尔
    void printarr();
};

#endif // CARRAY_H

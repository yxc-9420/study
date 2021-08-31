#include "carraysort.h"
#include<algorithm>

/**
 * @brief researchPivot 寻找基准值，并返回循环交换后的位置
 * @param arr 数组
 * @param start 开始位置
 * @param end 结束位置
 * @return
 */
int researchPivot(int *arr,int start,int end){
    int base = arr[start];//18
    int temp;
    while(start<end){
        while(arr[start] < base && start < end){
            //找出第一个不小于基准值的位置
            start++;
        }
        while(arr[end] > base && start < end){
            //找出第一个不大于基准值的位置
            end--;
        }
        //交换数据
        if(start < end){
            temp=*(arr+start);
            *(arr+start) = *(arr+end);
            *(arr+end) = temp;
        }
    }
    return start;
}

/**
 * @brief quicksort 快速排序具体实现
 * @param arr 数组
 * @param start 开始位置
 * @param end 结束位置
 */
void quicksort(int *arr,int start,int end){
    //查找基准位置
    if(start<end){
        int pivot = researchPivot(arr,start,end);
        quicksort(arr,0,pivot-1);
        quicksort(arr,pivot+1,end);
    }
}

template <class T>
void swap(T &a,T &b){
    a = a^b;
    b = b^a;  //b = b^a^b = a
    a = b^a;  //a = a^ a^ b = b;
}

/**
 * @brief CArray::bubblesort 冒泡排序
 */
void CArray::bubblesort()
{
    for(int i=0;i<length-1;i++){
        bool flag = true;//若已排好序，则为true
        for(int j = 0;j<length-1-i;j++){
            if(arr[j]>arr[j+1]){
                //交换
                arr[j] ^=arr[j+1];
                arr[j+1] ^= arr[j];
                arr[j] ^= arr[j+1];
                flag = false;
            }
        }
        if(flag) break;
    }
}

/**
 * @brief CArray::quicksort 快速排序
 */
void CArray::quicksort()
{
    ::quicksort(arr,0,length-1);
}

/**
 * @brief CArray::selectsort 选择排序
 * 每次选择最小的数，依次放到数组头
 */
void CArray::selectsort()
{
    for(int i = 0; i<length-1;i++){
        int minIndex = i;
        for(int j=i+1;j<length-1;j++){
            if(arr[j]<arr[minIndex]){
                minIndex = j;
            }
        }
        if(minIndex!=i){
            ::swap(arr[minIndex],arr[i]);
        }
    }
}

/**
 * @brief CArray::insertsort 插入排序
 * 从前到后，依次选择元素插入到 已排序元素中
 */
void CArray::insertsort()
{
    int insertIndex;//待插入索引
    int temp;//临时值
    for(int i = 1;i<length;i++){//从索引1开始，每个元素找到待插入的索引
        insertIndex = i;
        for(int j=0;j<i;j++){//再已排序的数组中查找当前待插入数据的索引。
            if(arr[i]<arr[j]) {
                insertIndex = j;
                break;
            }
        }
        temp = arr[i];
        //从index到i-1 向后移，并把i处的值移到index处
        for(int k = i-1;k>=insertIndex;k--){
            arr[k+1] = arr[k];
        }
        arr[insertIndex] = temp;
    }
}

/**
 * @brief CArray::heapsort 堆排序
 */
void CArray::heapsort()
{

}

/**
 * @brief CArray::countsort 计数排序，适用于最大数不是很大且序列较集中的时候
 */
void CArray::countsort()
{
    vector<int> v(arr,arr+length);
    int maxNum = *std::max_element(v.begin(),v.end());
    vector<int> vcount(maxNum+1);
    for(int a:v)vcount[a]++;
    int index = 0;
    for(int i = 0;i<maxNum+1;i++){
        while (vcount[i]-->0) {
            arr[index++] = i;
        }
    }
}

void CArray::mergesort()
{

}

void CArray::bucketsort()
{

}

/**
 * @brief CArray::radixsort 基数排序
 */
void CArray::radixsort()
{
    vector<int> v(arr,arr+length);
    int maxNum = *max_element(v.begin(),v.end());
    int maxDigit = 0;
    while(maxNum>0){
        maxDigit++;
        maxNum /=10;
    }
    int mod = 10;
    int div = 1;
    vector<vector<int>> container(10);//初始化10个空vector<int>
    for(int i = 0;i<maxDigit;i++,mod*=10,div*=10){
        //个位开始，逐位
        for(int j=0;j<length;j++){
            int bucket = (arr[j]%mod)/div;//从最低位逐个取数
            container[bucket].push_back(arr[j]);
        }
        int pos = 0;
        int siz = container.size();
        for(int i=0;i<siz;i++){
            if(!container[i].empty()){
                //桶内排序
                std::sort(container[i].begin(),container[i].end(),//默认升序
                          [](int &x,int &y){return x>y;});//lamda 自定义降序，参数用引用捕获
                while (!container[i].empty()) {
//                    arr[pos++] = container[i].front();
//                    container[i].erase(container[i].begin());//升序时使用
                    arr[pos++] = container[i].back();
                    container[i].pop_back();//降序时使用
                }
            }
        }
    }
}

/**
 * @brief CArray::shellsort 希尔排序
 */
void CArray::shellsort()
{
    for(int gap = length/2;gap>0;gap/=2){
        //执行插入排序
        for(int i = gap;i<length;i++){
            int j = i;
            int current = arr[i];
            while(j-gap>=0 && current<arr[j-gap]){
                arr[j] = arr[j-gap];
                j-=gap;
            }
            arr[j] = current;
        }
    }
}

void CArray::printarr()
{
    for(int i=0;i<length;i++){
        std::cout<<*(arr+i)<<" ";
    }
    std::cout<<std::endl;
}

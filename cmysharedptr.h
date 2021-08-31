#ifndef CMYSHAREDPTR_H
#define CMYSHAREDPTR_H
#include<iostream>
#include<assert.h>
using namespace std;
template <typename T>
class CMySharedPtr
{
public:
    CMySharedPtr(T* ptr = nullptr);
    //拷贝构造
    CMySharedPtr(const CMySharedPtr &ptr);
    //赋值构造
    CMySharedPtr& operator=(const CMySharedPtr &ptr);
    //析构
    ~CMySharedPtr(){
        (*_count)--;
        if(*_count==0){
            delete _ptr;
            delete  _count;
        }
    }
    T& operator *(){
        assert(_ptr==nullptr);
        return *_ptr;
    }

    T* operator ->(){
        assert(_ptr==nullptr);
        return _ptr;
    }

    size_t getUsed(){
        return *_count;
    }
private:
    T *_ptr;
    size_t * _count;
};
template <typename T>
CMySharedPtr<T>::CMySharedPtr(T* ptr){
    _ptr=ptr;
    if(ptr){
        _count = new size_t(1);
    }
    else{
        _count = new size_t(0);
    }
}
/**
 * 拷贝构造
 */
template <typename T>
CMySharedPtr<T>::CMySharedPtr(const CMySharedPtr<T>& ptr){
    if(this != &ptr){
        _ptr = ptr._ptr;
        _count = ptr._count;
        (*_count)++;
    }
}

/**
 * 赋值构造
 */
template <typename T>
CMySharedPtr<T>& CMySharedPtr<T>::operator=(const CMySharedPtr<T> &ptr){
    if(_ptr == ptr._ptr){
        return *this;
    }
    if(_ptr){
        if(--(*_count) == 0){
            delete _ptr;
            delete _count;
        }
    }
    _ptr = ptr._ptr;
    _count = ptr._count;
    (*_count)++;
    return *this;
}

#endif // CMYSHAREDPTR_H

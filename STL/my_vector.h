#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include<memory>
#include<malloc.h>
using namespace std;
template<class T,class Alloc =__gnu_cxx::new_allocator<T>>
class my_vector
{
public:

    typedef T value_type;
    typedef size_t size_type ;
    typedef value_type* pointer ;
    typedef value_type* iterator ;
    typedef T& reference ;

    my_vector():start(0),finish(0),end_of_storage(0){};
    iterator begin(){return start;}
    iterator end(){return finish;}
    size_type size(){return end()-begin();}
    size_type capacity(){return end_of_storage-begin();}
    reference operator[](size_type n);
    reference front(){return *begin();}
    reference back(){return *(end()-1);}
    void push_back(const T& x);

protected:
    iterator start;
    iterator finish;
    iterator end_of_storage;
private:
    void insert_aux(iterator position,const T& x);
};

template<class T, class Alloc>
void my_vector<T,Alloc>::push_back(const T &x)
{
    if(finish != end_of_storage){
        //剩余容量充足
        _Construct(finish,x);
        ++finish;
    }
    else{
        insert_aux(end(),x);
    }
}

template<class T, class Alloc>
void my_vector<T,Alloc>::insert_aux(iterator position,const T &x)
{
    if(finish != end_of_storage){
        _Construct(finish,*(finish-1));
        ++finish;
        copy_backward(position,finish-2,finish-1);//从后向前拷贝元素
        *position = x;
    }
    else{
        const size_type old_size = size();
        const size_type new_size = old_size==0?1:old_size*2;
        //分配内存
        __gnu_cxx::new_allocator<T> alloc;

        iterator new_start = alloc.allocate(new_size);
        iterator new_finish = new_start;
        try{
            new_finish = uninitialized_copy(start,position,new_start);
            _Construct(new_finish,x);
            new_finish++;
            new_finish =uninitialized_copy(position,finish,new_finish);
        } catch (...) {
            _Destroy(new_start,new_finish);
            alloc.deallocate(new_start,new_size);
        }
        //析构原 vector对象
        _Destroy(begin(),end());
        //释放原 vector内存
        alloc.deallocate(start,end_of_storage-start);

        //调整迭代器
        start = new_start;
        finish = new_finish;
        end_of_storage = start+new_size;
    }
}


#endif // MY_VECTOR_H

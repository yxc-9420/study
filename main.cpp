#include<iterator>
#include "carraysort.h"
#include"cmysharedptr.h"
#include<fstream>
class base{
//    ~base(){} 私有析构函数，阻止在栈上创建对象
//    base(){}  私有构造函数，阻止在栈上创建对象
//    void* operator new(size_t val){} 重载new，私有化，阻止在堆上创建对象
public:
    virtual void g(int a = 10){cout<<"base::g(),a:"<<a<<endl;}
};

class de:public base{
    public:
    virtual void g(int a = 20){cout<<"de::g(),a:"<<a<<endl;}
};

extern int a = 3;

int& ceshi(){
    return a;
}

int main()
{
    ofstream file("test.txt",ios::out);
    if(file.is_open()){
        file<<"line 1\n";
        file<<"line 2\n";
        file.close();
    }
    else
        cout<<"Unable to open this file"<<endl;

    ifstream ifile("test.txt",ios::binary);
    if(ifile.is_open()){
        streampos begin = ifile.tellg();
        ifile.seekg(0,ios::end);
        streampos end = ifile.tellg();
        ifile.close();
        cout<<"this file's size is "<<(end-begin)<<" bytes.\n";
    }
    else
        cout<<"Unable to open this file"<<endl;

    CMySharedPtr<int> myptr(new int(1));
    cout<<myptr.getUsed()<<endl;//1
    CMySharedPtr<int>ptr1(myptr);
    cout<<ptr1.getUsed()<<endl;//2
    CMySharedPtr<int>ptr2(new int(20));
    cout<<ptr2.getUsed()<<endl;//1
    ptr1 = ptr2;
    cout<<myptr.getUsed()<<endl;//1
    cout<<ptr1.getUsed()<<endl;//2
    cout<<ptr2.getUsed()<<endl;//2

    int arr[] = {99,2,33,44,55,0,4,7,34,76,89,10,18};
    CArray myArr(arr,sizeof (arr)/sizeof(int));

    cout<<"before sorted:";
    myArr.printarr();
    //myArr.selectsort();
    //myArr.bubblesort();
    //myArr.quicksort();
    //myArr.insertsort();
    //myArr.countsort();
    myArr.radixsort();
    cout<<"after radixsort sorted:";
    myArr.printarr();

    base* ba =new de;
    ba->g();//base::g(),a:10

    vector<int> v(5); //5个0
    v.emplace_back(4);//
    ostream_iterator<double> iter_double(cout," ");
    copy(v.begin(),v.end(),iter_double);

    system("pause");
    return 0;
}

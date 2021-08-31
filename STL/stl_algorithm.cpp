#include<iostream>
#include<iterator>
#include<algorithm>
#include<numeric>
using namespace std;
template <class T>
struct dispaly{
public:
    void operator()(T& t){
        cout<<t<<" ";
    }
};

int main(int argc, char* argv[]){
    int a[] = {0,1,2,3,4,5,6,7,8,9};
    int b[10];
    copy(a,a+10,b);//b: 0,1,2,3,4,5,6,7,8,9
    int* res = copy(a,a+5,a+2);//a:0,1,0,1,2,3,4,7,8,9 此处没覆盖 详见源码
    reverse_iterator<int>(begin(a));

    //返回值指向 目的地开始处+复制元素个数
    cout<<"a:"<<&(*a)<<endl;
    cout<<"res:"<<res<<endl;
    cout<<res-&(*a)<<endl;
    cout<<"a:";
    for_each(a,a+10,dispaly<int>());
    cout<<endl;
    cout<<"b:";
    for_each(b,b+10,dispaly<int>());
    cout<<endl;
    int sum = accumulate(b,b+5,0);
    cout<<"sum:"<<sum<<endl;

    getchar();
}

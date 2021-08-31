#include"csimplefactory.h"
int main(int argc,char *argv[]){
    Factory f;
    cout<<"请输入产品型号:"<<endl;
    string pname;
    while(cin>>pname){
        AbstractProduct *p = f.getProduct(pname);
        if(!p){
            cout<<"实例化失败"<<endl;
            return -1;
        }
        p->print();
        delete p;
    }
}

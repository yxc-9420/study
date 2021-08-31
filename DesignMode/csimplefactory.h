#ifndef CSIMPLEFACTORY_H
#define CSIMPLEFACTORY_H

#include<iostream>
#include<string>
using namespace std;

class AbstractProduct{
public:
    AbstractProduct(){}
    virtual ~AbstractProduct(){}
    virtual void print()=0;
};

class Product1:public AbstractProduct{
public:
    Product1(){
    }
    ~Product1(){}
    void print() override{
        cout<<"product1"<<endl;
    }
};
class Product2:public AbstractProduct{
public:
    Product2(){
    }
    ~Product2(){}
    void print() override{
        cout<<"Product2"<<endl;
    }
};

class Factory{
public:
    AbstractProduct* getProduct(string productName){
        if(productName =="p1"){
            return new Product1();
        }
        else if(productName=="p2"){
            return new Product2();
        }
        return nullptr;
    }
};

#endif // CSIMPLEFACTORY_H

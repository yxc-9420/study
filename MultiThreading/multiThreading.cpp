#include<iostream>
#include<mutex>
#include<thread>
#include<semaphore.h>
using namespace std;
void func1();
void func2();
static int count=0;
mutex mtx;
pthread_mutex_t mute;
sem_t first;
sem_t second;
int main(int argc,char* argv[])
{
    //pthread_mutex_init(&mute,nullptr);
    sem_init(&first,0,1);
    sem_init(&second,0,0);
    thread t1(func1);
    thread t2(func2);
    t1.join();
    t2.join();
    cout<<count<<endl;
    return 0;
}

void func1(){
    while(true){
        if(count>20) break;
        //lock_guard<mutex> lock_mutex(mtx);
        sem_wait(&first);//被用来阻塞当前线程直到信号量sem的值大于0，解除阻塞后将sem的值减一，表明公共资源经使用后减少
        //pthread_mutex_lock(&mute);
        cout<<"func1:"<<count<<"\n";
        count++;
        //pthread_mutex_unlock(&mute);
        sem_post(&second);//用来增加信号量的值
    }
}

void func2(){
    while(true){
        if(count>20) break;
        //lock_guard<mutex> lock_mutex(mtx);
        sem_wait(&second);//被用来阻塞当前线程直到信号量sem的值大于0，解除阻塞后将sem的值减一，表明公共资源经使用后减少
        //pthread_mutex_lock(&mute);
        cout<<"func2:"<<count<<"\n";
        count++;
        //pthread_mutex_unlock(&mute);
        sem_post(&first);//用来增加信号量的值
    }
}

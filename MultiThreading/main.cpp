#include"cthreadpool.h"
//int CThreadPool::s_thread_count = 4;
#include<cstring>
#include<semaphore.h>
#include<future>
mutex mtx;
condition_variable cv;
sem_t sem_A;
sem_t sem_B;
sem_t sem_C;
int flag=0;

void printA(int count){
    for(int i=0;i<count;i++){
        sem_wait(&sem_A);
        cout<<"A"<<endl;
        sem_post(&sem_B);
    }
}

void printB(int count){
    for(int i=0;i<count;i++){
        sem_wait(&sem_B);
        cout<<"B"<<endl;
        sem_post(&sem_C);
    }
}

void printC(int count){
    for(int i=0;i<count;i++){
        sem_wait(&sem_C);
        cout<<"C"<<endl;
        sem_post(&sem_A);
    }
}

//按顺序循环打印ABC
void print(int num)
{
    for(int i = 0 ; i<10;i++){
        unique_lock<mutex> lock(mtx);//获取锁
        cv.wait(lock,[&](){return flag == num;});//释放锁 并进入等待，直到条件满足后，等待唤醒，重新获得锁.
        cout<<"thread id:"<<this_thread::get_id()<<" print "<<char('A'+flag)<<endl;
        flag = (flag+1)%3;
        cv.notify_all();//不能用notify_one()，避免全部阻塞
    }
}

void getValueWaitFor(int second,promise<int>& p){
    std::this_thread::sleep_for(std::chrono::seconds(second));
    p.set_value(1);
}

bool testAsync(int a){
    this_thread::sleep_for(std::chrono::seconds(2));
    cout<<"start"<<endl;
    if(a%2==0)return true;
    return false;
}

int main(int argc,char *argv[]){
    int second = 1;
    promise<int> p;
    future<int> fu = p.get_future();
    std::thread t (getValueWaitFor,second,ref(p));//线程
    int a = fu.get();//valid属性，未准备好时，阻塞当前线程
    cout<<"ceshi"<<" "<<a<<endl;
    //t.join();

    packaged_task<bool(int)> pt(testAsync);

    //std::future<bool> fb = std::async(testAsync,3);
    std::future<bool> fb2 = std::async([&]{return testAsync(second);});
    //获取当前时间
    time_t now = time(nullptr);
    cout<<ctime(&now)<<":"<<"start wait"<<endl;
    //等待返回结果
    fb2.wait();
    //获取当前时间
    time_t now1 = time(nullptr);
    cout<<ctime(&now1)<<":"<<"finish wait"<<endl;

    bool bl = fb2.get();
    if(bl) cout<<"是偶数"<< endl;
    else cout<<"是基数"<<endl;
//    thread a(print,0);
//    thread b(print,1);
//    thread c(print,2);

//    sem_init(&sem_A,1,1);
//    sem_init(&sem_B,1,0);
//    sem_init(&sem_C,1,0);
//    thread A(printA,10);
//    thread B(printB,10);
//    printC(10);

    //CThreadPool ctp;
    //ctp.start();
    //this_thread::sleep_for(chrono::microseconds(500));
    system("pause");
}

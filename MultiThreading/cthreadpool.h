#ifndef CTHREADPOOL_H
#define CTHREADPOOL_H
#include <mutex>
#include <condition_variable>//""先在当前文件夹寻找此文件，如果失败，再去标准库寻找
#include <iostream> //<>会在C++标准库寻找
#include<functional>
#include<vector>
#include<queue>
#include<thread>
#include<future>
#include<iterator>
using namespace std;
//工作队列(线程队列) => 获取任务 =>执行任务
//任务队列
//互斥锁 获取任务时需要获取锁，避免一个任务被多个线程执行
//条件变量 工作队列，当没有任务时，会阻塞   任务队列，添加任务时唤醒工作队列

//开始：将指定数量线程加入线程队列，线程所绑定的函数，执行轮询 获取任务 =>执行任务
//结束：
class CThreadPool
{
    using Task = function<void()>;
public:
    static int s_thread_count;
    CThreadPool(int thread_count = 4);
    ~CThreadPool();
    void addTask(Task&);
    void start();
    void ThreadLoop();
    void stop();
    template<class T,class... Args>
    auto commit(T&& f,Args&... args) ->future<decltype (f(args...))>;
private:
    mutex m_mtx;//互斥锁
    condition_variable m_cv;//条件阻塞
    queue<Task> m_tasks;//任务队列
    vector<thread> m_pool;//线程池
    bool m_Run;
};

#endif // CTHREADPOOL_H

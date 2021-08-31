#include "cthreadpool.h"
CThreadPool::CThreadPool(int thread_count)
{
    CThreadPool::s_thread_count = thread_count;
}

CThreadPool::~CThreadPool()
{
    if(m_Run){
        stop();
    }
}

void CThreadPool::addTask(Task& task)
{
    //将task加入任务队列
    unique_lock<mutex> lock(m_mtx);
    m_tasks.push(task);
    m_cv.notify_one();
}

void CThreadPool::start()
{
    m_Run = true;

    for(int i = 0;i<CThreadPool::s_thread_count;i++){
        //thread t(bind(&CThreadPool::ThreadLoop,this));
        m_pool.emplace_back(
                    [this](){
            cout<<"ThreadPool:start() tid:"<<this_thread::get_id()<<"start."<<endl;
            while (m_Run) {
                //取任务并执行
                Task task;
                //取任务需加锁
                {
                    unique_lock<mutex>lock(m_mtx);
                    if(!m_Run || m_tasks.empty()){
                        cout<<"ThreadPool:start() tid:"<<this_thread::get_id()<<"wait."<<endl;
                        m_cv.wait(lock);
                    }
                    //m_cv.wait(lock,m_Run && !m_tasks.empty());
                    cout<<"ThreadPool:start() tid:"<<this_thread::get_id()<<"wakeup."<<endl;
                    if(m_Run && !m_tasks.empty()){
                        task = m_tasks.back();
                        m_tasks.pop();
                    }
                }
                //执行
                task();
            }
            cout<<"ThreadPool:start() tid:"<<this_thread::get_id()<<"end."<<endl;
        }
        );
    }
}

void CThreadPool::ThreadLoop()
{
    cout<<"ThreadPool:start() tid:"<<this_thread::get_id()<<"start."<<endl;
    while (m_Run) {
        //取任务并执行
        Task task;
        //取任务需加锁
        {
            unique_lock<mutex>lock(m_mtx);
            if(!m_Run || m_tasks.empty()){
                cout<<"ThreadPool:start() tid:"<<this_thread::get_id()<<"wait."<<endl;
                m_cv.wait(lock);
            }
            cout<<"ThreadPool:start() tid:"<<this_thread::get_id()<<"wakeup."<<endl;
            if(m_Run && !m_tasks.empty()){
                task = m_tasks.back();
                m_tasks.pop();
            }
        }
        //执行
        task();
    }
    cout<<"ThreadPool:start() tid:"<<this_thread::get_id()<<"end."<<endl;
}

void CThreadPool::stop()
{
    //唤醒线程
    cout<<"ThreadPool::stop().stop"<<endl;
    m_Run = false;
    m_cv.notify_all();
    cout<<"ThreadPool::stop notify_all()."<<endl;
    for(vector<thread>::iterator it = m_pool.begin();it!=m_pool.end();it++){
        (*it).join();
        //delete *it;
    }
    m_pool.clear();
}

template<class T, class... Args>
auto CThreadPool::commit(T&& f,Args&... args) -> future<decltype (f(args...))>
{
    using ret_type = decltype (f(args...));
    auto task = make_shared<packaged_task<ret_type()>>(bind(forward<T>(f),forward<Args>(args)...));
    //定义一个智能指针，其指向内容为 返回值为ret_type的函数 ，用bind函数进行初始化。
    future<ret_type> res = task->get_future();
    {
        std::unique_lock<std::mutex>lock(m_mtx);
        if(!m_Run){
            throw std::runtime_error("current threadpool is stop");
        }
        m_tasks.emplace([task](){(*task)();});
    }
    m_cv.notify_one();
    return res;
}

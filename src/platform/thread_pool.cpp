#include "thread_pool.h"
#include "thread.h"
#include "task.h"

#include <thread>
#include <atomic>
#include <mutex>
#include <iostream>
#ifdef _WIN32
// 和protobuf头文件会有冲突 ，protobuf的头文件要在windows.h之前
#include <windows.h>
#else
#include <signal.h>
#endif

using namespace std;

/// 管理所有线程对象
static atomic<bool> is_exit_all(false);
static vector<Thread *> all_threads;
static mutex all_threads_mutex;

void ThreadPool::ExitAllThread()
{
    is_exit_all = true;
    all_threads_mutex.lock();
    for (auto t : all_threads)
    {
        t->Exit();
    }
    all_threads_mutex.unlock();
    this_thread::sleep_for(200ms);
}

void ThreadPool::Wait()
{
    while (!is_exit_all)
    {
        this_thread::sleep_for(1000ms);
    }
}

class CThreadPool : public ThreadPool
{
public:
    void Init(int thread_count)
    {
        this->thread_count_ = thread_count;
        this->last_thread_ = -1;
        for (int i = 0; i < thread_count; i++)
        {
            Thread *t = new Thread();
            t->set_id(i + 1);
            t->Start();
            this->threads_.push_back(t);
            all_threads_mutex.lock();
            all_threads.push_back(t);
            all_threads_mutex.unlock();
        }
    }

    void Dispatch(Task *task)
    {
        /// 轮询方式
        if (!task)
            return;

        int tid = (this->last_thread_ + 1) % this->thread_count_;
        this->last_thread_ = tid;
        Thread *t = this->threads_[tid];

        /// 添加任务
        t->AddTask(task);

        /// 激活线程
        t->Activate();
    }

private:
    /// 线程池线程数量
    int thread_count_ = 0;
    /// 上一次分发到的线程，用于轮询
    int last_thread_ = -1;
    /// 线程池线程列表
    std::vector<Thread *> threads_;
};

ThreadPool *ThreadPoolFactory::Create()
{
    /// socket库初始化
    static mutex mtx;
    static bool is_init = false;
    mtx.lock();
    if (!is_init)
    {

#ifdef _WIN32
        WSADATA wsa;
        WSAStartup(MAKEWORD(2, 2), &wsa);
#else
        if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
            return nullptr;
#endif
        is_init = true;
    }
    mtx.unlock();
    return new CThreadPool();
}

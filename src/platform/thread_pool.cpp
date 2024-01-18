#include "thread_pool.h"
#include "thread.h"
#include "task.h"

#include <thread>
#include <atomic>
#include <mutex>
#include <iostream>
#ifdef _WIN32
// ��protobufͷ�ļ����г�ͻ ��protobuf��ͷ�ļ�Ҫ��windows.h֮ǰ
#include <windows.h>
#else
#include <signal.h>
#endif

using namespace std;

/// ���������̶߳���
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
        /// ��ѯ��ʽ
        if (!task)
            return;

        int tid = (this->last_thread_ + 1) % this->thread_count_;
        this->last_thread_ = tid;
        Thread *t = this->threads_[tid];

        /// �������
        t->AddTask(task);

        /// �����߳�
        t->Activate();
    }

private:
    /// �̳߳��߳�����
    int thread_count_ = 0;
    /// ��һ�ηַ������̣߳�������ѯ
    int last_thread_ = -1;
    /// �̳߳��߳��б�
    std::vector<Thread *> threads_;
};

ThreadPool *ThreadPoolFactory::Create()
{
    /// socket���ʼ��
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

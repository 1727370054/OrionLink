#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#ifdef _WIN32
#ifdef XCOM_EXPORTS
#define XCOM_API __declspec(dllexport)
#else
#define XCOM_API __declspec(dllimport)
#endif
#else
#define XCOM_API
#endif // _WIN32

#include <vector>

class Thread;
class Task;

class XCOM_API ThreadPool
{
public:
    ThreadPool() {}
    ~ThreadPool(){}

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 初始化所有线程对象并启动线程, 会调用每个线程对象对应的 Start 函数
    /// 来初始化线程
    /// @param thread_count 线程池线程数量
    virtual void Init(int thread_count) = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 分发任务到线程中执行，会调用 task 的 Init 进行任务初始化
    /// 任务会轮询分发到线程池中的各个线程
    /// @param task 任务接口对象，XTask 需要用户自己继承并重载 Init 函数
    virtual void Dispatch(Task * task) = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 退出所有的线程
    static void ExitAllThread();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 阻塞等待 ExitAllThread
    static void Wait();
};

class XCOM_API ThreadPoolFactory
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief 创建线程池
    static ThreadPool* Create();
};

#endif // THREAD_POOL_H

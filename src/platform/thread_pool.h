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
    /// @brief ��ʼ�������̶߳��������߳�, �����ÿ���̶߳����Ӧ�� Start ����
    /// ����ʼ���߳�
    /// @param thread_count �̳߳��߳�����
    virtual void Init(int thread_count) = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief �ַ������߳���ִ�У������ task �� Init ���������ʼ��
    /// �������ѯ�ַ����̳߳��еĸ����߳�
    /// @param task ����ӿڶ���XTask ��Ҫ�û��Լ��̳в����� Init ����
    virtual void Dispatch(Task * task) = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief �˳����е��߳�
    static void ExitAllThread();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief �����ȴ� ExitAllThread
    static void Wait();
};

class XCOM_API ThreadPoolFactory
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// @brief �����̳߳�
    static ThreadPool* Create();
};

#endif // THREAD_POOL_H

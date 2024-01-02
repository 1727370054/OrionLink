#ifndef THREAD_H
#define THREAD_H

#include <list>
#include <mutex>

class Task;

class Thread
{
public:
    Thread();
    ~Thread();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 创建线程，并调用Setup()函数创建通信读写管道，设置线程分离
    void Start();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 线程回调函数，在自己的 event_base 进行事件循环
    void Main();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 创建通信读写管道，建立每个线程对应的event_base，监听读端
    /// @return bool 创建通信读写管道和event_base是否成功
    ///////////////////////////////////////////////////////////////////////////
    bool Setup();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 监听读端事件就绪回调函数
    /// @param fd 读端文件句柄
    /// @param which 事件类型
    void Notify(int fd, short which);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 添加具体任务到线程对应的任务队列中，记录任务与线程 event_base 的关联
    /// @param task 用户添加的具体任务
    void AddTask(Task * task);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 向管道写数据，用于唤醒线程
    void Activate();

    void set_id(const int id) { id_ = id; }
    const int id() { return id_; }

    void Exit()
    {
        is_exit_ = true;
    }
private:
    bool is_exit_ = false;
    int id_;
    int notify_send_fd_;
    struct event_base * base_;

    /// 任务列表
    std::list<Task*> tasks_;
    std::mutex tasks_mutex_;
};

#endif // THREAD_H


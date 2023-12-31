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
    /// @brief �����̣߳�������Setup()��������ͨ�Ŷ�д�ܵ��������̷߳���
    void Start();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief �̻߳ص����������Լ��� event_base �����¼�ѭ��
    void Main();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ����ͨ�Ŷ�д�ܵ�������ÿ���̶߳�Ӧ��event_base����������
    /// @return bool ����ͨ�Ŷ�д�ܵ���event_base�Ƿ�ɹ�
    ///////////////////////////////////////////////////////////////////////////
    bool Setup();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ���������¼������ص�����
    /// @param fd �����ļ����
    /// @param which �¼�����
    void Notify(int fd, short which);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ��Ӿ��������̶߳�Ӧ����������У���¼�������߳� event_base �Ĺ���
    /// @param task �û���ӵľ�������
    void AddTask(Task * task);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief ��ܵ�д���ݣ����ڻ����߳�
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

    /// �����б�
    std::list<Task*> tasks_;
    std::mutex tasks_mutex_;
};

#endif // THREAD_H


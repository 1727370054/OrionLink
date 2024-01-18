#ifndef TASK_H
#define TASK_H

#ifdef _WIN32
#ifdef XCOM_EXPORTS
#define XCOM_API __declspec(dllexport)
#else
#define XCOM_API __declspec(dllimport)
#endif
#else
#define XCOM_API
#endif // _WIN32

class XCOM_API Task
{
public:

    ///////////////////////////////////////////////////////////////////////////
    /// @brief �û��ľ�������ʵ�ֺ������û���Ҫ�̳д˽ӿ��࣬������ʵ�ִ˷���
    /// @return ��ʼ���Ƿ�ɹ�
    ///////////////////////////////////////////////////////////////////////////
    virtual bool Init() = 0;

    void set_base(struct event_base* base) { base_ = base; }
    const struct event_base* base(){ return base_; }

    void set_sock(int sock) { sock_ = sock; }
    const int sock() { return sock_; }

    void set_thread_id(int id){ thread_id_ = id; }
    const int thread_id()  { return thread_id_; }

protected:
    struct event_base * base_ = nullptr;
    int sock_ = 0;
    int thread_id_ = 0;
};

#endif

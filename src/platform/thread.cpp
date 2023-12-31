#include "thread.h"
#include "task.h"
#include "tools.h"

#include <thread>
#include <functional>
#include <iostream>
#include <event2/event.h>
#include <event2/util.h>

#ifdef _WIN32
#else
#include <unistd.h>
#endif // _WIN32

using namespace std;

Thread::Thread()
    :id_(0), notify_send_fd_(0), base_(nullptr)
{
}

Thread::~Thread()
{
}

void Thread::Start()
{
    Setup();

    std::thread t(&Thread::Main, this);

    t.detach();
}

void Thread::Main()
{
    std::stringstream ss;
    ss << id_ << " Thread::Main() begin";
    LOGINFO(ss.str().c_str());

    if (!base_)
    {
        LOGERROR("Thread::Main() - base is null, failed!");
        LOGERROR("In windows set WSAStartup(MAKEWORD(2, 2), &was);");
        return;
    }

    while (!is_exit_)
    {
        /// һ�δ�������Ϣ
        event_base_loop(base_, EVLOOP_NONBLOCK);
        this_thread::sleep_for(1ms);
    }

    event_base_free(base_);

    ss.clear();
    ss << id_ << " Thread::Main() end";
    LOGINFO(ss.str().c_str());
}


/// �����߳�����ص�����
static void NotifyCallBack(int fd, short what, void * arg)
{
    Thread * t = static_cast<Thread *>(arg);
    if (!t)
    {
        LOGERROR("NotifyCallBack - this is null");
        return;
    }
    t->Notify(fd, what);
}

void Thread::Notify(int fd, short what)
{
    char buf[2] = { 0 };
#ifdef _WIN32
    int result = recv(fd, buf, 1, 0);
#else
    int result = read(fd, buf, 1);
#endif // _WIN32
    if (result <= 0)
        return;

    std::stringstream ss;
    ss << id_ << " recv " << buf;
    LOGDEBUG(ss.str().c_str());

    /// ��ȡ����,��ʼ������
    Task * task = nullptr;
    tasks_mutex_.lock();
    if (tasks_.empty())
    {
        tasks_mutex_.unlock();
        return;
    }
    task = tasks_.front();
    tasks_.pop_front();
    tasks_mutex_.unlock();

    task->Init();
}

bool Thread::Setup()
{
#ifdef _WIN32
    /// ����socket pair ����ͨ�ţ�fds[0]: �� fds[1]: д
    evutil_socket_t fds[2];
    if (evutil_socketpair(AF_INET, SOCK_STREAM, 0, fds) < 0)
    {
        LOGERROR("evutil_socketpair failed! ");
        return false;
    }
    /// ���óɷ�����
    evutil_make_socket_nonblocking(fds[0]);
    evutil_make_socket_nonblocking(fds[1]);
#else
    // linux �ܵ�
    int fds[2];
    if (pipe(fds))
    {
        LOGERROR("pipe failed! ");
        return false;
    }
#endif // _WIN32

    /// ��ȡ�󶨵�event�¼����У�д��Ҫ����
    this->notify_send_fd_ = fds[1];

    /// ����libevent������(����)
    event_config * ev_conf = event_config_new();
    event_config_set_flag(ev_conf, EVENT_BASE_FLAG_NOLOCK);
    this->base_ = event_base_new_with_config(ev_conf);
    event_config_free(ev_conf);
    if (!base_)
    {
        LOGERROR("event_base_new_with_config failed! ");
        return false;
    }

    /// ��ӹܵ������¼������ڼ����߳�ִ������
    event * ev = event_new(base_, fds[0], EV_READ | EV_PERSIST, NotifyCallBack, this);
    event_add(ev, 0);
    
    return true;
}

void Thread::AddTask(Task * task)
{
    if (!task)
        return;

    task->set_base(this->base_);
    task->set_thread_id(this->id_);
    tasks_mutex_.lock();
    tasks_.push_back(task);
    tasks_mutex_.unlock();
}

void Thread::Activate()
{
#ifdef _WIN32
    int result = send(this->notify_send_fd_,"c", 1, 0);
#else
    int result = write(this->notify_send_fd_, "c", 1);
#endif // _WIN32
    if (result <= 0)
    {
        LOGERROR("XThread::Activate() failed! ");
    }
}
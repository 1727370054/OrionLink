﻿#include "com_task.h"
#include "tools.h"

#include <iostream>
#include <mutex>
#include <cstring>
#include <event2/event.h>
#include <event2/bufferevent.h>

using namespace std;

static void SReadCallback(struct bufferevent* bev, void* arg)
{
    auto task = static_cast<ComTask*>(arg);
    if (!task) return;
    task->ReadCallback();
}

static void SWriteCallback(struct bufferevent* bev, void* arg)
{
    auto task = static_cast<ComTask*>(arg);
    if (!task) return;
    task->WriteCallback();
}

static void SEventCallback(struct bufferevent* bev,short what ,void* arg)
{
    auto task = static_cast<ComTask*>(arg);
    if (!task) return;
    task->EventCallback(what);
}

void ComTask::set_server_ip(const char* ip)
{
    strncpy(this->server_ip_, ip, sizeof(server_ip_));
}

ComTask::ComTask()
{
    mtx_ = new std::mutex();
}

ComTask::~ComTask()
{
    delete mtx_;
}

bool ComTask::InitBufferevent(int sock)
{
    /// -1：自动创建socket
    bev_ = bufferevent_socket_new(base_, sock, BEV_OPT_CLOSE_ON_FREE);
    if (!bev_)
    {
        LOGERROR("bufferevent_socket_new failed!");
        return false;
    }

    /// 设置回调
    bufferevent_setcb(bev_, SReadCallback, SWriteCallback, SEventCallback, this);
    bufferevent_enable(bev_, EV_READ | EV_WRITE);

    //timeval tl = { 10, 0 };
    //bufferevent_set_timeouts(bev_, &tl, &tl);

    return true;
}

bool ComTask::Connect()
{
    /// bufferevent 建立连接
    struct sockaddr_in remote;
    memset(&remote, 0, sizeof(remote));
    remote.sin_family = AF_INET;
    remote.sin_port = htons(server_port_);
    evutil_inet_pton(AF_INET, server_ip_, &remote.sin_addr.s_addr);

    Mutex lock(mtx_);
    is_connected_ = false;
    is_connecting_ = false;
    if (!bev_) InitBufferevent(-1);
    if (!bev_)
    {
        LOGERROR("ComTask::Connect - bev is null");
        return false;
    }

    int ret = bufferevent_socket_connect(bev_, (struct sockaddr*)&remote, sizeof(remote));
    if (ret != 0)
    {
        LOGERROR("ComTask::Init() - connect remote failed!");
        is_connecting_ = false;
        return false;
    }

    is_connecting_ = true;
    return true;
}

bool ComTask::Init()
{
    /// 区分服务端还是客户端
    int comsocket = this->sock();
    if (comsocket <= 0)
        comsocket = -1;

    {
        Mutex lock(mtx_);
        InitBufferevent(comsocket);
    }

    if (server_ip_[0] == '\0')
        return true;

    return Connect();
}

void ComTask::Close()
{
    {
        Mutex lock(mtx_);
        is_connected_ = false;
        is_connecting_ = false;

        if (bev_) bufferevent_free(bev_);
        bev_ = NULL;
    }
    if (auto_delete_ )
    {
        delete this;
    }
}

int ComTask::Read(void* data, int size)
{
    if (!bev_)
    {
        LOGERROR("bev not set");
        return 0;
    }
    int len = bufferevent_read(bev_, data, size);
    return len;
}

void ComTask::TriggerWrite()
{
    if (!bev_) return;
    bufferevent_trigger(bev_, EV_WRITE, 0);
}

bool ComTask::Write(const void* data, int size)
{
    Mutex lock(mtx_);
    if (!bev_ || !data || size <= 0) return false;

    int ret = bufferevent_write(bev_, data, size);
    if (ret != 0) return false;

    return true;
}

void ComTask::EventCallback(short what)
{
    if (what & BEV_EVENT_CONNECTED)
    {
        LOGDEBUG("event: BEV_EVENT_CONNECTED");
        std::stringstream ss;
        ss << "connect server " << server_ip_ << ":" << server_port_ << " success!";
        LOGINFO(ss.str().c_str());
        is_connected_ = true;
        is_connecting_ = false;
        ConnectCallback();
    }

    /// 退出要处理缓冲问题
    if (what & BEV_EVENT_ERROR || what & BEV_EVENT_TIMEOUT)
    {
        LOGERROR("BEV_EVENT_ERROR or BEV_EVENT_TIMEOUT");
        Close();
    }
    if (what & BEV_EVENT_EOF)
    {
        LOGERROR("BEV_EVENT_EOF");
        Close();
    }
}

bool ComTask::WaitConnected(int timeout_sec)
{
    /// 10 秒监听一次
    int count = timeout_sec * 100;
    for (int i = 0; i < count; i++)
    {
        if (is_connected())
            return true;
        this_thread::sleep_for(10ms);
    }
    return is_connected();
}

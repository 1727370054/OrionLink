#include "service.h"
#include "tools.h"

#include <event2/listener.h>
#include <event2/bufferevent.h>

static void SListenCallback(struct evconnlistener* evc, evutil_socket_t client_socket,
    struct sockaddr* client_addr, int socklen, void* arg)
{
    LOGDEBUG("ListenCallback");
    auto task = static_cast<Service*>(arg);
    task->ListenCallback(client_socket, client_addr, socklen);
}

Service::Service()
{
    thread_listen_pool_ = ThreadPoolFactory::Create();
    thread_handle_pool_ = ThreadPoolFactory::Create();
}

Service::~Service()
{
    delete thread_listen_pool_;
    thread_listen_pool_ = nullptr;
    delete thread_handle_pool_;
    thread_handle_pool_ = nullptr;
}

bool Service::Init()
{
    if (server_port_ <= 0)
    {
        LOGERROR("server port not set");
        return false;
    }
    /// 绑定端口
    sockaddr_in local;
    memset(&local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(server_port_);
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    auto evc = evconnlistener_new_bind(base_, SListenCallback, this,
        LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,
        10,
        (sockaddr*)&local,
        sizeof(local)
    );
    if (evc == nullptr)
    {
        std::stringstream ss;
        ss << "listen port " << server_port_ << " failed!";
        LOGERROR(ss.str().c_str());
        return false;
    }
    std::stringstream ss;
    ss << "listen port " << server_port_ << " success!";
    LOGINFO(ss.str().c_str());

    return true;
}

bool Service::Start()
{
    thread_listen_pool_->Init(1);
    thread_handle_pool_->Init(thread_count_);

    thread_listen_pool_->Dispatch(this);
    return true;
}

void Service::ListenCallback(int client_socket, sockaddr* client_addr, int socklen)
{
    auto handle = CreateServiceHandle();
    handle->set_sock(client_socket);
    char ip[16] = { 0 };
    int port = 0;
    auto addr = (struct sockaddr_in*)client_addr;
    evutil_inet_ntop(AF_INET, &addr->sin_addr.s_addr, ip, sizeof(ip));
    port = ntohs(addr->sin_port);
    std::stringstream ss;
    ss << "accept client ip: " << ip << " client port: " << port;
    LOGINFO(ss.str().c_str());

    handle->set_client_ip(ip);
    handle->set_client_port(port);

    /// 加入到线程池
    thread_handle_pool_->Dispatch(handle);
}

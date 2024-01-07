#include "service_proxy.h"
#include "msg_comm.pb.h"
#include "register_client.h"
#include "tools.h"

#include <thread>

using namespace std;
using namespace msg;

ServiceProxy::ServiceProxy()
{
}

ServiceProxy::~ServiceProxy()
{
}

void ServiceProxy::DeleteEvent(MsgEvent* event)
{
    if (!event) return;
    Mutex lock(&callbacks_mutex_);
    auto call = callbacks_.find(event);
    if (call == callbacks_.end())
    {
        LOGERROR("Delete event failed, not find");
        return;
    }
    call->second->DeleteEvent(event);
    callbacks_.erase(event);
}

bool ServiceProxy::SendMsg(msg::MsgHead* head, Msg* msg, MsgEvent* event)
{
    /// 1. 负载均衡找到微服务的连接

    if (!head || !msg) return false;
    string service_name = head->service_name();
    Mutex lock_guard(&client_map_mutex_);
    auto client_list = client_map_.find(service_name);
    if (client_list == client_map_.end())
    {
        stringstream ss;
        ss << service_name << " client_map_ not find";
        LOGDEBUG(ss.str().c_str());
        return false;
    }

    /// 轮询找到上一次的微服务连接
    int cur_index = client_map_last_index_[service_name];
    int list_size = client_list->second.size();
    for (int i = 0; i < list_size; i++)
    {
        cur_index++;
        cur_index = cur_index % list_size;
        client_map_last_index_[service_name] = cur_index;
        auto client = client_list->second[cur_index];
        if (client->is_connected())
        {
            /// 用于退出清理
            {
                Mutex lock(&callbacks_mutex_);
                callbacks_[event] = client;
            }

            /// 转发消息到微服务
            return client->SendMsg(head, msg, event);
        }
    }
    LOGDEBUG("can't find proxy");
    return false;
}

void ServiceProxy::Start()
{
    thread th(&ServiceProxy::Main, this);
    th.detach();
}

void ServiceProxy::Stop()
{
    is_exit_ = true;
}

void ServiceProxy::Main()
{
    while (!is_exit_)
    {
        /// 从注册中心获取微服务列表的更新
        /// 定时全部重新获取

        RegisterClient::GetInstance()->GetServiceListReq(NULL);
        auto service_map = RegisterClient::GetInstance()->GetAllServiceList();
        if (!service_map)
        {
            LOGDEBUG("service_map is empty");
            this_thread::sleep_for(1s);
            continue;
        }
        auto smap = service_map->service_map();
        if (smap.empty())
        {
            LOGDEBUG("service_map->service_map() is empty");
            this_thread::sleep_for(1s);
            continue;
        }

        /// 遍历所有的微服务名称列表
        for (const auto& m : smap)
        {
            /// 遍历单个微服务
            for (const auto& s : m.second.service())
            {
                /// 此微服务是否已经连接
                string service_name = s.name();

                /// 不连接自己
                if (service_name == API_GATEWAY_NAME)
                    continue;

                Mutex lock_guard(&client_map_mutex_);
                /// 第一个微服务创建对象，开启连接
                if (client_map_.find(service_name) == client_map_.end())
                {
                    client_map_[service_name] = vector<ServiceProxyClient*>();
                }
                /// 列表是否有此微服务
                bool isfind = false;
                for (const auto& c : client_map_[service_name])
                {
                    if (c->server_ip() == s.ip() && c->server_port() == s.port())
                    {
                        isfind = true;
                        break;
                    }
                }
                if (isfind)
                    continue;

                auto proxy = new ServiceProxyClient();
                proxy->set_server_ip(s.ip().c_str());
                proxy->set_server_port(s.port());
                proxy->set_auto_delete(false); /// 设置关闭后对象自动清理
                proxy->StartConnect();
                client_map_[service_name].push_back(proxy);
                client_map_last_index_[service_name] = 0;
            }
        }

        for (const auto & m : client_map_)
        {
            for (const auto& c : m.second)
            {
                if (c->is_connected())
                    continue;
                if (!c->is_connecting())
                {
                    c->Connect();
                }
            }
        }
        this_thread::sleep_for(3000ms);
    }
}




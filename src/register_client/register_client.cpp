#include "register_client.h"
#include "msg_comm.pb.h"
#include "tools.h"

using namespace std;
using namespace msg;

static ServiceMap* service_map = nullptr;
static ServiceMap* client_map = nullptr;
static mutex  service_map_mutex;

RegisterClient::RegisterClient()
{
}

RegisterClient::~RegisterClient()
{
}

void RegisterClient::RegisterMsgCallback()
{
    RegisterCallback(MSG_REGISTER_RES, (MsgCBFunc)&RegisterClient::RegisterRes);
    RegisterCallback(MSG_GET_SERVICE_RES, (MsgCBFunc)&RegisterClient::GetServiceRes);
}

msg::ServiceMap* RegisterClient::GetAllServiceList()
{
    Mutex lock(&service_map_mutex);
    if (!service_map)
        return NULL;
    if (!client_map)
        client_map = new ServiceMap();
    client_map->CopyFrom(*service_map);
    return client_map;
}

msg::ServiceMap::ServiceList RegisterClient::GetServices(const char* service_name, int timeout_sec)
{
    msg::ServiceMap::ServiceList list;
    /// 10毫秒判断一次
    int total_count = timeout_sec * 100;
    int count = 0;
    /// 1.等待连接成功 
    while (count < total_count)
    {
        if (is_connected())
            break;
        this_thread::sleep_for(10ms);
        count++;
    }
    if (!is_connected())
    {
        LOGDEBUG("连接等待超时");
        return list;
    }
    
    /// 2.发送获取微服务列表请求
    GetServiceListReq(service_name);
 
    /// 3.等待获取微服务消息反馈(有可能拿到上一次的内容)
    while (count < total_count)
    {
        Mutex lock(&service_map_mutex);
        if (!service_map)
        {
            this_thread::sleep_for(10ms);
            count++;
            continue;
        }
        auto m = service_map->mutable_service_map();
        if (m->empty() || !m)
        {
            /// 还没有找到指定微服务
            GetServiceListReq(service_name);
            this_thread::sleep_for(100ms);
            count += 10;
            continue;
        }
        auto iter = m->find(service_name);
        if (iter == m->end())
        {
            GetServiceListReq(service_name);
            this_thread::sleep_for(100ms);
            count += 10;
            continue;
        }
        list.CopyFrom(iter->second);
        return list;
    }

    return list;
}

void RegisterClient::RegisterRes(msg::MsgHead* head, Msg* msg)
{
    LOGDEBUG("接收到注册服务的响应");
    msg::MessageRes response;
    if (!response.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("response parse failed!");
        return;
    }
    if (response.return_() == MessageRes::OK)
    {
        LOGDEBUG("微服务注册成功!");
        return;
    }
    stringstream ss;
    ss << "微服务注册失败! " << response.desc();
    LOGDEBUG(ss.str().c_str());
}

void RegisterClient::GetServiceRes(msg::MsgHead* head, Msg* msg)
{
    LOGDEBUG("获取服务列表的响应");
    Mutex lock(&service_map_mutex);
    if (!service_map)
        service_map = new ServiceMap();
    if (!service_map->ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("ServiceMap ParseFromArray failed!");
        return;
    }
}

void RegisterClient::GetServiceListReq(const char* service_name)
{
    LOGDEBUG("发送获取微服务列表");
    GetServiceReq request;
    request.set_type(GetServiceReq::ALL);
    if (service_name)
    {
        request.set_type(GetServiceReq::ONE);
        request.set_name(service_name);
    }
    SendMsg(MSG_GET_SERVICE_REQ, &request);
}

void RegisterClient::ConnectCallback()
{
    /// 发送注册消息
    LOGDEBUG("注册中心客户端连接成功，开始发送注册请求");
    RegisterReq request;
    request.set_name(service_name_);
    request.set_ip(service_ip_);
    request.set_port(service_port_);
    SendMsg(MSG_REGISTER_REQ, &request);
}

void RegisterClient::RegisterService(const char* service_name, const char* ip, int port)
{
    RegisterClient::RegisterMsgCallback();
    if (service_name)
        strcpy(service_name_, service_name);
    if (ip)
        strcpy(service_ip_, ip);
    if (port > 0)
        service_port_ = port;

    StartConnect();
}
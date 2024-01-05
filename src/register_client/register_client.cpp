#include "register_client.h"
#include "msg_comm.pb.h"
#include "tools.h"

using namespace std;
using namespace msg;

static ServiceMap* service_map = nullptr;
static ServiceMap* client_map = nullptr;
static mutex  service_map_mutex;

/// 单例模式锁
std::mutex RegisterClient::mutex_;

RegisterClient::RegisterClient()
{
}

RegisterClient::~RegisterClient()
{
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

void RegisterClient::RegisterMsgCallback()
{
    RegisterCallback(MSG_REGISTER_RES, (MsgCBFunc)& RegisterClient::RegisterRes);
    RegisterCallback(MSG_GET_SERVICE_RES, (MsgCBFunc)&RegisterClient::GetServiceRes);
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
    LOGDEBUG(service_map->DebugString().c_str());
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
#include "register_handle.h"
#include "msg_comm.pb.h"
#include "tools.h"

using namespace std;
using namespace msg;

/// 注册服务列表的缓存
static ServiceMap* service_map = nullptr;
static mutex  service_map_mutex;

void RegisterHandle::RegisterMsgCallback()
{
    RegisterCallback(MSG_HEART_REQ, (MsgCBFunc)&RegisterHandle::HeartRes);
    RegisterCallback(MSG_REGISTER_REQ, (MsgCBFunc) &RegisterHandle::RegisterReq);
    RegisterCallback(MSG_GET_SERVICE_REQ, (MsgCBFunc)&RegisterHandle::GetServiceReq);
}

void RegisterHandle::RegisterReq(msg::MsgHead* head, Msg* msg)
{
    LOGDEBUG("注册中心的服务端接收到注册请求");

    /// 回应的消息
    msg::MessageRes response;

    msg::RegisterReq request;
    if (!request.ParseFromArray(msg->data, msg->size))
    {
        string error = "register request parse failed!";
        LOGDEBUG(error.c_str());
        response.set_return_(MessageRes::ERROR);
        response.set_desc(error.c_str());
        SendMsg(MSG_REGISTER_RES, &response);
        return;
    }

    string service_name = request.name();
    if (service_name.empty())
    {
        string error = "service name is empty!";
        LOGDEBUG(error.c_str());
        response.set_return_(MessageRes::ERROR);
        response.set_desc(error.c_str());
        SendMsg(MSG_REGISTER_RES, &response);
        return;
    }

    string service_ip = request.ip();
    if (service_ip.empty())
    {
        LOGDEBUG("service ip is empty!");
        service_ip = this->client_ip();
    }

    int service_port = request.port();
    if (service_port <= 0 || service_port > 65535)
    {
        stringstream error;
        error << "service port is error!, port: " << service_port;
        LOGDEBUG(error.str().c_str());
        response.set_return_(MessageRes::ERROR);
        response.set_desc(error.str().c_str());
        SendMsg(MSG_REGISTER_RES, &response);
        return;
    }

    stringstream ss;
    ss << "接收到客户端注册请求: " << service_name << " " << service_ip << " " << service_port;
    LOGINFO(ss.str().c_str());

    /// 存储微服务注册信息，如果已经注册需要更新
    {
        Mutex lock(&service_map_mutex);
        if (!service_map)
            service_map = new ServiceMap();
        auto smap = service_map->mutable_service_map();
        /// 判断同一微服务类型是否已经注册
        auto service_list = smap->find(service_name);
        if (service_list == smap->end())
        {
            (*smap)[service_name] = ServiceMap::ServiceList();
            service_list = smap->find(service_name);
        }
        auto services = service_list->second.mutable_service();
        /// 查找该请求的微服务信息ip和port是否已经被注册过了
        for (const auto& service : (*services))
        {
            if (service.ip() == service_ip && service.port() == service_port)
            {
                stringstream ss;
                ss << service_name << " " << service_ip << ":" 
                    << service_port << " 该微服务已经注册过";
                LOGDEBUG(ss.str().c_str());
                response.set_return_(MessageRes::ERROR);
                response.set_desc(ss.str().c_str());
                SendMsg(MSG_REGISTER_RES, &response);
                return;
            }
        }

        /// 添加新的微服务
        auto service = service_list->second.add_service();
        service->set_name(service_name);
        service->set_ip(service_ip);
        service->set_port(service_port);
    }
    
    stringstream info;
    info << service_name << " " << service_ip << ":"
        << service_port << " 新的微服务注册成功!";
    LOGDEBUG(info.str().c_str());
    response.set_return_(MessageRes::OK);
    response.set_desc("register service success!");
    SendMsg(MSG_REGISTER_RES, &response);
}

void RegisterHandle::GetServiceReq(msg::MsgHead* head, Msg* msg)
{
    msg::GetServiceReq request;

    /// 错误处理
    msg::ServiceMap response;
    response.mutable_response()->set_return_(msg::MessageRes::ERROR);
    if (!request.ParseFromArray(msg->data, msg->size))
    {
        string error = "Failed to resolve the service discovery request";
        LOGDEBUG(error.c_str());
        response.mutable_response()->set_desc(error.c_str());
        SendMsg(MSG_GET_SERVICE_RES, &response);
        return;
    }
    
    stringstream ss;
    string service_name = request.name();
    ss << "获取到发现服务请求 service name: " << service_name;
    LOGDEBUG(ss.str().c_str());
    msg::ServiceMap* send_map = &response;

    /// 发送所有微服务数据
    service_map_mutex.lock();
    if (!service_map) service_map = new ServiceMap();

    /// 返回全部
    if (request.type() == ServiceType::ALL)
    {
        send_map = service_map;
    }
    else
    {
        auto smap = service_map->mutable_service_map();
        if (smap && smap->find(service_name) != smap->end())
        {
            (*send_map->mutable_service_map())[service_name] = (*smap)[service_name];
        }
    }
    service_map_mutex.unlock();

    send_map->set_type(request.type());
    send_map->mutable_response()->set_return_(msg::MessageRes::OK);
    SendMsg(MSG_GET_SERVICE_RES, send_map);
}
#include "log_client.h"
#include "config_handle.h"
#include "msg_comm.pb.h"
#include "config_dao.h"
#include "tools.h"

using namespace std;
using namespace msg;

void ConfigHandle::RegisterMsgCallback()
{
    RegisterCallback(MSG_SAVE_CONFIG_REQ, (MsgCBFunc)&ConfigHandle::SaveConfig);
    RegisterCallback(MSG_LOAD_CONFIG_REQ, (MsgCBFunc)&ConfigHandle::LoadConfig);
    RegisterCallback(MSG_LOAD_ALL_CONFIG_REQ, (MsgCBFunc)&ConfigHandle::LoadAllConfig);
    RegisterCallback(MSG_DEL_CONFIG_REQ, (MsgCBFunc)&ConfigHandle::DeleteConfig);
}

void ConfigHandle::SaveConfig(msg::MsgHead* head, Msg* msg)
{
    LOGDEBUG("接收到保存配置的请求");
    MessageRes response;
    Config config;
    if (!config.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("ConfigHandle::SaveConfig failed! ParseFromArray error");
        response.set_return_(MessageRes::ERROR);
        response.set_desc("format error");
        SendMsg(MSG_SAVE_CONFIG_RES, &response);
        return;
    }
    if (config.service_ip().empty())
        config.set_service_ip(this->client_ip());
    if (!ConfigDao::GetInstance()->SaveConfig(&config))
    {
        LOGDEBUG("ConfigHandle::SaveConfig failed! save error");
        response.set_return_(MessageRes::ERROR);
        response.set_desc("save failed");
        SendMsg(MSG_SAVE_CONFIG_RES, &response);
        return;
    }
    response.set_return_(MessageRes::OK);
    response.set_desc("save success");
    SendMsg(MSG_SAVE_CONFIG_RES, &response);
}

void ConfigHandle::LoadConfig(msg::MsgHead* head, Msg* msg)
{
    LOGDEBUG("接收到下载配置的请求");
    LoadConfigReq request;
    if (!request.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("ConfigHandle::LoadConfig failed! ParseFromArray error");
        return;
    }
    /// 根据IP和端口获取配置项
    string service_ip = request.service_ip();
    if (service_ip.empty())
        service_ip = this->client_ip();
    Config config = ConfigDao::GetInstance()->LoadConfig(service_ip.c_str(), request.service_port());
    SendMsg(MSG_LOAD_CONFIG_RES, &config);
}

void ConfigHandle::LoadAllConfig(msg::MsgHead* head, Msg* msg)
{
    LOGDEBUG("接收到下载全部配置的请求");
    LoadAllConfigReq request;
    if (!request.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("ConfigHandle::LoadAllConfig failed! ParseFromArray error");
        return;
    }
    auto confs = ConfigDao::GetInstance()->LoadAllConfig(request.page(), request.page_count());
    SendMsg(MSG_LOAD_ALL_CONFIG_RES, &confs);
}

void ConfigHandle::DeleteConfig(msg::MsgHead* head, Msg* msg)
{
    LOGDEBUG("接收到删除配置的请求");
    LoadConfigReq request;
    /// 响应信息
    MessageRes response;
    if (!request.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("ConfigHandle::DeleteConfig failed! ParseFromArray error");
        response.set_return_(MessageRes::ERROR);
        response.set_desc("ParseFromArray error");
        SendMsg(MSG_DEL_CONFIG_RES, &response);
        return;
    }
    if (!ConfigDao::GetInstance()->DeleteConfig(request.service_ip().c_str(), request.service_port()))
    {
        LOGDEBUG("ConfigHandle::DeleteConfig failed! DeleteConfig error");
        response.set_return_(MessageRes::ERROR);
        response.set_desc("Delete error, DAO failed");
        SendMsg(MSG_DEL_CONFIG_RES, &response);
        return;
    }
    response.set_return_(MessageRes::OK);
    response.set_desc("Delete config success");
    SendMsg(MSG_DEL_CONFIG_RES, &response);
}

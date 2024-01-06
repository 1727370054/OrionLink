#include "config_handle.h"
#include "msg_comm.pb.h"
#include "config_dao.h"
#include "tools.h"

using namespace std;
using namespace msg;

void ConfigHandle::RegisterMsgCallback()
{
    RegisterCallback(MSG_SAVE_CONFIG_REQ, (MsgCBFunc)&ConfigHandle::SaveConfig);
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

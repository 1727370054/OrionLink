#include "config_client.h"
#include "msg_comm.pb.h"
#include "tools.h"

using namespace msg;
using namespace std;

std::mutex ConfigClient::mutex_;

void ConfigClient::RegisterMsgCallback()
{
    RegisterCallback(MSG_SAVE_CONFIG_RES, (MsgCBFunc)&ConfigClient::RecvConfigRes);
}

void ConfigClient::SendConfigReq(msg::Config *config)
{
    SendMsg(MSG_SAVE_CONFIG_REQ, config);
}

void ConfigClient::RecvConfigRes(msg::MsgHead* head, Msg* msg)
{
    MessageRes response;
    if (!response.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("ConfigClient::RecvConfigRes failed! ParseFromArray error");
        return;
    }
    if (response.return_() == MessageRes::OK)
    {
        LOGDEBUG("上传配置成功!");
        return;
    }

    stringstream ss;
    ss << "上传配置失败: " << response.desc();
    LOGDEBUG(ss.str().c_str());
}

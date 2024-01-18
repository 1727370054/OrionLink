#include "log_handle.h"
#include "log_dao.h"
#include "msg_comm.pb.h"

using namespace std;
using namespace msg;

void LogHandle::RegisterMsgCallback()
{
    RegisterCallback(MSG_ADD_LOG_REQ, (MsgCBFunc)&LogHandle::AddLogReq);
}

void LogHandle::AddLogReq(msg::MsgHead* head, Msg* msg)
{
    msg::AddLogReq request;
    if (!request.ParseFromArray(msg->data, msg->size))
    {
        cerr << "AddLogReq failed! ParseFromArray error" << endl;
        return;
    }

    if (request.service_ip().empty())
    {
        request.set_service_ip(this->client_ip());
    }

    LogDAO::GetInstance()->AddLog(&request);
}

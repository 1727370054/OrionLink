#include "get_dir_client.h"
#include "ifile_manager.h"
#include "msg_comm.pb.h"

#include <iostream>

using namespace std;
using namespace msg;
using namespace disk;

void GetDirClient::RegisterMsgCallback()
{
    RegisterCallback((MsgType)GET_DIR_RES, (MsgCBFunc)&GetDirClient::GetDirRes);
}

void GetDirClient::GetDirReq(disk::GetDirReq req)
{
    cur_dir_ = req.root();
    SendMsg((MsgType)GET_DIR_REQ, &req);
}

void GetDirClient::GetDirRes(msg::MsgHead* head, Msg* msg)
{
    FileInfoList file_list;
    if (!file_list.ParseFromArray(msg->data, msg->size))
    {
        cerr << "GetDirClient::GetDirRes failed! ParseFromArray error" << endl;
        return;
    }

    cout << file_list.DebugString() << endl;

    iFileManager::GetInstance()->RefreshData(file_list, cur_dir_);
}

GetDirClient::GetDirClient()
{
    set_service_name(DIR_NAME);
}

GetDirClient::~GetDirClient()
{
}

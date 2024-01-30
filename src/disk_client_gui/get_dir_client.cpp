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
    RegisterCallback((MsgType)NEW_DIR_RES, (MsgCBFunc)&GetDirClient::NewDirRes);
    RegisterCallback((MsgType)DELETE_FILE_RES, (MsgCBFunc)&GetDirClient::DeleteFileRes);
    RegisterCallback((MsgType)GET_DISK_INFO_RES, (MsgCBFunc)&GetDirClient::GetDiskInfoRes);
}

void GetDirClient::GetDirReq(disk::GetDirReq& req)
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

    GetDiskInfoReq();
}

void GetDirClient::NewDirReq(std::string path)
{
    disk::GetDirReq req;
    req.set_root(path);
    SendMsg((MsgType)NEW_DIR_REQ,&req);
}

void GetDirClient::NewDirRes(msg::MsgHead* head, Msg* msg)
{
    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::seconds>(now - last_exec_time_).count() < 1)
    {
        // 如果距离上次执行不足1秒，直接返回
        return;
    }

    // 更新执行时间
    last_exec_time_ = now;

    disk::GetDirReq req;
    req.set_root(cur_dir_);
    SendMsg((MsgType)GET_DIR_REQ, &req);
}

void GetDirClient::DeleteFileReq(disk::FileInfo file_info)
{
    SendMsg((MsgType)DELETE_FILE_REQ, &file_info);
}

void GetDirClient::DeleteFileRes(msg::MsgHead* head, Msg* msg)
{
    disk::GetDirReq req;
    req.set_root(cur_dir_);
    SendMsg((MsgType)GET_DIR_REQ, &req);
}

void GetDirClient::GetDiskInfoReq()
{
    MessageRes req;
    req.set_desc("GET");
    SendMsg((MsgType)GET_DISK_INFO_REQ, &req);
}

void GetDirClient::GetDiskInfoRes(msg::MsgHead* head, Msg* msg)
{
    DiskInfo res;
    if (!res.ParseFromArray(msg->data, msg->size))
    {
        cerr << "GetDirClient::GetDiskInfoRes failed! ParseFromArray error" << endl;
        return;
    }

    iFileManager::GetInstance()->RefreshDiskInfo(res);
}

GetDirClient::GetDirClient()
{
    set_service_name(DIR_NAME);
}

GetDirClient::~GetDirClient()
{
}

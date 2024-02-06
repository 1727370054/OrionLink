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
    RegisterCallback(MSG_GET_OUT_SERVICE_RES, (MsgCBFunc)&GetDirClient::GetServiceRes);
    RegisterCallback((MsgType)RENAME_RES, (MsgCBFunc)&GetDirClient::RenameRes);
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
    /// 获取上传下载服务器列表
    GetService();
    /// 刷新磁盘空间使用情况
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

void GetDirClient::DeleteFileReq(disk::FileInfo& file_info)
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

void GetDirClient::RenameReq(std::string& old_filename, std::string& new_filename)
{
    disk::RenameReq req;
    req.set_old_filename(old_filename);
    req.set_new_filename(new_filename);
    SendMsg((MsgType)RENAME_REQ, &req);
}

void GetDirClient::RenameRes(msg::MsgHead* head, Msg* msg)
{
    MessageRes res;
    if (!res.ParseFromArray(msg->data, msg->size))
    {
        cerr << "GetDirClient::RenameRes failed! ParseFromArray error" << endl;
        return;
    }

    if (res.return_() == MessageRes::OK)
    {
        iFileManager::GetInstance()->RefreshDir();
    }
    else
    {
        iFileManager::GetInstance()->RefreshDir();
        iFileManager::GetInstance()->ErrorSig("重命名失败! 可能有同名文件");
    }
}

void GetDirClient::TimerCallback()
{
    //GetService();
}

void GetDirClient::GetService()
{
    GetServiceReq req;
    req.set_name(UPLOAD_NAME);
    SendMsg(MSG_GET_OUT_SERVICE_REQ, &req);

    req.set_name(DOWNLOAD_NAME);
    SendMsg(MSG_GET_OUT_SERVICE_REQ, &req);
}

void GetDirClient::GetServiceRes(msg::MsgHead* head, Msg* msg)
{
    ServiceList res;
    if (!res.ParseFromArray(msg->data, msg->size))
    {
        cerr << "XGetDirClient::GetServiceRes failed! ParseFromArray error" << endl;
        return;
    }

    if (res.name() == UPLOAD_NAME)
        iFileManager::GetInstance()->set_upload_servers(res);
    else if (res.name() == DOWNLOAD_NAME)
        iFileManager::GetInstance()->set_download_servers(res);
}

GetDirClient::GetDirClient()
{
    set_service_name(DIR_NAME);
}

GetDirClient::~GetDirClient()
{
}

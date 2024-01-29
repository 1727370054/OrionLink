#include "dir_handle.h"
#include "log_client.h"
#include "tools.h"
#include "msg_comm.pb.h"
#include "disk_client_gui.pb.h"

using namespace disk;
using namespace msg;
using namespace std;

#ifdef _WIN32
#define DIR_ROOT "./server_root/"
#else
#define DIR_ROOT "/mnt/orion_link/"
#endif // _WIN32


void DirHandle::RegisterMsgCallback()
{
    RegisterCallback((MsgType)GET_DIR_REQ, (MsgCBFunc)&DirHandle::GetDirReq);
    RegisterCallback((MsgType)NEW_DIR_REQ, (MsgCBFunc)&DirHandle::NewDirReq);
    RegisterCallback((MsgType)DELETE_FILE_REQ, (MsgCBFunc)&DirHandle::DeleteFileReq);
}

void DirHandle::GetDirReq(msg::MsgHead* head, Msg* msg)
{
    /// 根目录 + 用户名 + 相对目录
    string path = DIR_ROOT;
    path += head->username();
    path += "/";
    disk::GetDirReq req;
    if (!req.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("DirHandle::GetDirReq failed! ParseFromArray error");
        return;
    }
    path += req.root();
    auto files = GetDirList(path);
    FileInfoList file_list;
    for (const auto& file : files)
    {
        if (file.filename == "." || file.filename == "..")
            continue;
        auto info = file_list.add_files();
        info->set_filename(file.filename);
        info->set_filesize(file.filesize);
        info->set_filetime(file.time_str);
        info->set_is_dir(file.is_dir);
    }
    head->set_msg_type((MsgType)GET_DIR_RES);
    SendMsg(head, &file_list);
}

void DirHandle::NewDirReq(msg::MsgHead* head, Msg* msg)
{
    string path = DIR_ROOT;
    path += head->username();
    path += "/";
    disk::GetDirReq req;
    if (!req.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("DirHandle::GetDirReq failed! ParseFromArray error");
        return;
    }
    path += req.root();
    NewDir(path);

    MessageRes res;
    res.set_return_(MessageRes::OK);
    res.set_desc("OK");
    head->set_msg_type((MsgType)NEW_DIR_RES);
    SendMsg(head, &res);
}

void DirHandle::DeleteFileReq(msg::MsgHead* head, Msg* msg)
{
    string path = DIR_ROOT;
    path += head->username();
    path += "/";
    disk::FileInfo req;
    if (!req.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("DirHandle::GetDirReq failed! ParseFromArray error");
        return;
    }
    path += req.filedir();
    path += "/";
    path += req.filename();
    DelFile(path, req.is_dir());

    MessageRes res;
    res.set_return_(MessageRes::OK);
    res.set_desc("OK");
    head->set_msg_type((MsgType)DELETE_FILE_RES);
    SendMsg(head, &res);
}

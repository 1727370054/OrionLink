#include "upload_handle.h"
#include "msg_comm.pb.h"
#include "log_client.h"
#include "tools.h"

using namespace std;
using namespace msg;
using namespace disk;

#ifdef _WIN32
#define DIR_ROOT "./server_root/"
#else
#define DIR_ROOT "/mnt/orion_link/"
#endif // _WIN32

#define FILE_INFO_NAME_PRE ".info_"

void UploadHandle::RegisterMsgCallback()
{
    RegisterCallback((MsgType)UPLOAD_FILE_REQ, (MsgCBFunc)&UploadHandle::UploadFileReq);
    RegisterCallback((MsgType)SEND_SLICE_REQ, (MsgCBFunc)&UploadHandle::SendSliceReq);
    RegisterCallback((MsgType)UPLOAD_FILE_END_REQ, (MsgCBFunc)&UploadHandle::UploadFileEndReq);
}

void UploadHandle::UploadFileReq(msg::MsgHead* head, Msg* msg)
{
    if (!cur_file_info_.ParseFromArray(msg->data, msg->size))
    {
        LOGERROR("UploadHandle::UploadFileReq failed, ParseFromArray error");
        return;
    }
    MessageRes res;
    string path = DIR_ROOT;
    path += head->username();
    path += "/";
    path += cur_file_info_.filedir();
    save_dir_ = path;
    NewDir(path);

    path += "/";
    path += cur_file_info_.filename();
    ofs_.open(path.c_str(), ios::binary);
    if (ofs_.is_open())
    {
        res.set_return_(MessageRes::OK);
        res.set_desc("ok");
    }
    else
    {
        res.set_return_(MessageRes::ERROR);
        res.set_desc("open file failed!");
    }
    head->set_msg_type((MsgType)UPLOAD_FILE_RES);
    SendMsg(head, &res);
}

void UploadHandle::SendSliceReq(msg::MsgHead* head, Msg* msg)
{
    head->set_msg_type((MsgType)SEND_SLICE_RES);
    MessageRes res;
    if (head->md5().empty())
    {
        LOGERROR("UploadHandle::SendSliceReq failed! md5 is empty!");
        //需要校验权限
        res.set_return_(MessageRes::ERROR);
        res.set_desc("md5 is empty");
        SendMsg(head, &res);
        return;
    }

    //校验md5
    string md5 = OLMD5_base64((unsigned char*)msg->data, msg->size);
    if (md5 != head->md5())
    {
        LOGERROR("UploadHandle::SendSliceReq failed! md5 is error!");
        res.set_return_(MessageRes::ERROR);
        res.set_desc("md5 is error");
    }

    ofs_.write(msg->data, msg->size);

    res.set_return_(MessageRes::OK);
    res.set_desc("ok");
    SendMsg(head, &res);
}

void UploadHandle::UploadFileEndReq(msg::MsgHead* head, Msg* msg)
{
    /// 缓存文件信息 .filename.info
    string info_path = save_dir_;
    info_path += "/";
    info_path += FILE_INFO_NAME_PRE;
    info_path += cur_file_info_.filename();
    ofstream ofs;
    ofs.open(info_path, ios::binary);
    if (ofs.is_open())
    {
        cur_file_info_.SerializeToOstream(&ofs);
        ofs.close();
    }

    ofs_.close();
    head->set_msg_type((MsgType)UPLOAD_FILE_END_RES);
    MessageRes res;
    res.set_return_(MessageRes::OK);
    res.set_desc("ok");
    SendMsg(head, &res);
}

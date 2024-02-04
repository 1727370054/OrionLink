#include "download_handle.h"
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
#define FILE_SLICE_BYTE 100000000 

DownloadHandle::DownloadHandle()
{
    slice_buf_ = new char[FILE_SLICE_BYTE];
}

DownloadHandle::~DownloadHandle()
{
    ifs_.close();
    delete[] slice_buf_;
    slice_buf_ = nullptr;
}

void DownloadHandle::RegisterMsgCallback()
{
    RegisterCallback((MsgType)DOWNLOAD_FILE_REQ, (MsgCBFunc)&DownloadHandle::DownloadFileReq);
    RegisterCallback((MsgType)DOWNLOAD_FILE_BEGTIN, (MsgCBFunc)&DownloadHandle::DownloadFileBegin);
    RegisterCallback((MsgType)DOWNLOAD_SLICE_RES, (MsgCBFunc)&DownloadHandle::DownloadSliceRes);
}

void DownloadHandle::DownloadFileReq(msg::MsgHead* head, Msg* msg)
{
    if (!file_.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("UploadFileReq ParseFromArray failed!");
        return;
    }
    /// 容错没有信息的情况，有客户端判断文件是否有效
    
    string path = DIR_ROOT;
    path += head->username();
    path += "/";
    path += file_.filedir();
    path += "/";
    string info_file = path;
    path += file_.filename();

    info_file += FILE_INFO_NAME_PRE;
    info_file += file_.filename();
    FileInfo re_file;
    ifstream ifs(info_file, ios::binary);
    if (ifs.is_open() && re_file.ParseFromIstream(&ifs))
    {
        LOGINFO("file info read success!");
        file_.CopyFrom(re_file);
    }
    ifs.close();

    head->set_msg_type((MsgType)DOWNLOAD_FILE_RES);
    ifs_.open(path, ios::binary);
    ifs_.seekg(0, ios::end);
    if (!ifs_.is_open())
    {
        /// 失败返回文件大小为0
        re_file.set_filesize(0);
        SendMsg(head, &re_file);
        return;
    }

    re_file.set_filesize(ifs_.tellg());
    ifs_.seekg(0, ios::beg);
    SendMsg(head, &re_file);
}

void DownloadHandle::DownloadFileBegin(msg::MsgHead* head, Msg* msg)
{
    SendSlice();
}

void DownloadHandle::DownloadSliceRes(msg::MsgHead* head, Msg* msg)
{
    SendSlice();
}

void DownloadHandle::SendSlice()
{
    if (ifs_.eof())
    {
        return;
    }

    int size = FILE_SLICE_BYTE;
    if (size > file_.filesize())
        size = file_.filesize();

    ifs_.read(slice_buf_, size);
    size = ifs_.gcount();

    MsgHead head;
    head.set_msg_type((MsgType)DOWNLOAD_SLICE_REQ);
    Msg data;
    data.data = slice_buf_;
    data.size = size;
    SendMsg(&head, &data);
}

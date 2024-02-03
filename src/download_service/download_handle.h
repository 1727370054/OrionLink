#ifndef DOWNLOAD_HANDLE_H
#define DOWNLOAD_HANDLE_H

#include "service_handle.h"
#include "disk_client_gui.pb.h"

#include <fstream>
#include <list>

class DownloadHandle : public ServiceHandle
{
public:
    DownloadHandle(); 
    ~DownloadHandle();

    static void RegisterMsgCallback();

    void DownloadFileReq(msg::MsgHead* head, Msg* msg);

    void DownloadFileBegin(msg::MsgHead* head, Msg* msg);

    void DownloadSliceRes(msg::MsgHead* head, Msg* msg);

private:
    void SendSlice();

    std::ifstream ifs_;
    disk::FileInfo file_;         /// 当前接收的文件
    disk::FileSlice cur_slice_;   /// 当前接收的文件片信息
    std::list<Msg> cur_data_;     /// 当前接收的文件片数据
    std::list<Msg> caches_;       /// 接收文件的缓存

    int filesize_ = 0;      /// 文件大小
    int sendsize_ = 0;      /// 已经发送的文件大小
    char* slice_buf_ = nullptr;
};

#endif // DOWNLOAD_HANDLE_H


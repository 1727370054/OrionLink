#ifndef UPLOAD_HANDLE_H
#define UPLOAD_HANDLE_H

#include "service_handle.h"
#include "disk_client_gui.pb.h"

#include <fstream>

class UploadHandle : public ServiceHandle
{
public:
    static void RegisterMsgCallback();

    void UploadFileReq(msg::MsgHead* head, Msg* msg);

    void SendSliceReq(msg::MsgHead* head, Msg* msg);

    void UploadFileEndReq(msg::MsgHead* head, Msg* msg);
private:
    std::string save_dir_ = "";
    disk::FileInfo cur_file_info_;
    std::ofstream ofs_;
    disk::FileSlice cur_slice_;       /// 当前接收的文件片信息
    std::list<Msg> cur_data_;         /// 当前接收的文件片数据
    std::list<Msg> caches_;           /// 接收文件的缓存
};

#endif // !UPLOAD_HANDLE_H


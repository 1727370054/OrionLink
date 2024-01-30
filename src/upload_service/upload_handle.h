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
    disk::FileInfo cur_file_info_;
    std::ofstream ofs_;
};

#endif // !UPLOAD_HANDLE_H


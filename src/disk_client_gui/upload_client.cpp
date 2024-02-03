#include "upload_client.h"
#include "ifile_manager.h"

using namespace std;
using namespace msg;
using namespace disk;

#define FILE_SLICE_BYTE 100000000

void UploadClient::RegisterMsgCallback()
{
    RegisterCallback((MsgType)UPLOAD_FILE_RES, (MsgCBFunc)&UploadClient::UploadFileRes);
    RegisterCallback((MsgType)SEND_SLICE_RES, (MsgCBFunc)&UploadClient::SendSliceRes);
    RegisterCallback((MsgType)UPLOAD_FILE_END_RES, (MsgCBFunc)&UploadClient::UploadFileEndRes);
}

void UploadClient::ConnectCallback()
{
    SendMsg((MsgType)UPLOAD_FILE_REQ, &file_info_);
    cout << "UploadClient::ConnectCallback" << endl;
}

bool UploadClient::set_file_info(disk::FileInfo& file_info)
{
    file_info_ = file_info;
    if (file_info.filedir() == "")
        file_info_.set_filedir("");
    ifs_.open(file_info.local_path(), ios::binary);
    if (!ifs_.is_open())
        return false;

}

void UploadClient::SendSlice()
{
    if (ifs_.eof())
    {
        /// 文件结尾，文件发送完成
        SendMsg((MsgType)UPLOAD_FILE_END_REQ, &file_info_);
        return;
    }
    int slice_size = FILE_SLICE_BYTE;
    if (slice_size > file_info_.filesize())
        slice_size = file_info_.filesize();

    /// 当前文件的偏移位置
    long long offset = ifs_.tellg();
    MsgHead head;
    head.set_msg_type((MsgType)SEND_SLICE_REQ);

    ifs_.read(slice_buf_, slice_size);
    slice_size = ifs_.gcount();

    Msg data;
    data.data = slice_buf_;
    data.size = slice_size;
    SetHead(&head);
    MsgEvent::SendMsg(&head, &data);
}

void UploadClient::UploadFileRes(msg::MsgHead* head, Msg* msg)
{
    cout << "UploadClient::UploadFileRes" << endl;
    /// 开始发送文件时，获取已经发送的值，要保证缓冲已经发送成功
    /// 根据协议，接收到该函数对应消息的反馈，缓冲已经发送完成 
    begin_send_data_size_ = send_data_size();
    /// 开始发送文件
    SendSlice();
}

void UploadClient::SendSliceRes(msg::MsgHead* head, Msg* msg)
{
    cout << "UploadClient::SendSliceRes" << endl;
    SendSlice();
}

void UploadClient::UploadFileEndRes(msg::MsgHead* head, Msg* msg)
{
    cout << "UploadClient::UploadFileEndRes" << endl;
    iFileManager::GetInstance()->RefreshDir();
    iFileManager::GetInstance()->UploadEnd(task_id);
    ifs_.close();
    //任务完成刷新界面
    ClearTimer();
    Close();
    DropInMsg();
}

void UploadClient::TimerCallback()
{
    if (begin_send_data_size_ < 0)
        return;
    auto size = BufferSize();

    int sended = send_data_size() - begin_send_data_size_ - size;
    cout << sended << " : " << file_info_.filesize() << endl;

    /// 如果数据过大，先缩小
    iFileManager::GetInstance()->UploadProcess(task_id, sended);
}

UploadClient::UploadClient()
{
    set_service_name(UPLOAD_NAME);
    slice_buf_ = new char[FILE_SLICE_BYTE];
}

UploadClient::~UploadClient()
{
    delete[] slice_buf_;
    slice_buf_ = nullptr;
}

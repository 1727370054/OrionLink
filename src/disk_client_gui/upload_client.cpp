#include "upload_client.h"
#include "ifile_manager.h"
#include "tools.h"

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

    int filesize = 0;
    /// 获取md5 每个FILE_SLICE_BYTE 生成一个片md5
    /// 所有的片md5，再生成一个文件md5
    /// 一开始就生成md5的目的是为了后面的秒传
    char md5_base64[17] = { 0 };
    string all_md5_base64 = "";
    while (!ifs_.eof())
    {
        ifs_.read(slice_buf_, FILE_SLICE_BYTE);
        int size = ifs_.gcount();
        filesize += size;

        string md5_base64 = OLMD5_base64((unsigned char*)slice_buf_, size);
        md5_base64s_.push_back(md5_base64);
        all_md5_base64 += md5_base64;
    }

    if (filesize == 0)
    {
        ifs_.close();
        return false;
    }
    /// 生成文件的md5 解密后校验，普通文件一开始就生成，加密文件不考虑秒传
    string file_md5 = OLMD5_base64((unsigned char*)all_md5_base64.c_str(), all_md5_base64.size());
    file_info_.set_md5(file_md5);

    file_info_.set_filesize(filesize);

    //如果是加密文件 文件大小补齐16的倍数
    if (file_info_.is_enc())
    {

        int dec_size = 0;
        if (filesize % 16 != 0)
        {
            dec_size = filesize + (16 - filesize % 16);
        }
        file_info_.set_filesize(dec_size);
        file_info_.set_ori_size(filesize);
    }
    ifs_.clear();
    ifs_.seekg(0, ios_base::beg);

    if (file_info_.is_enc())
    {
        auto pass = file_info_.password();
        if (pass.empty())
        {
            cerr << "please set password" << endl;
            return false;
        }
        if (!aes_)
        {
            aes_ = OLAES::Create();
        }
        aes_->SetKey(pass.c_str(), pass.size(), true);
    }
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
    head.set_offset(offset);

    if (slice_buf_ == nullptr)
    {
        Drop();
        return;
    }
    ifs_.read(slice_buf_, slice_size);
    slice_size = ifs_.gcount();

    Msg data;
    data.data = slice_buf_;
    data.size = slice_size;

    //如果需要加密
    if (file_info_.is_enc())
    {
        long long enc_size = 0;

        if (!aes_)
        {
            cerr << "aes not init!" << endl;
            return;
        }
        /// AES加密
        if (slice_buf_enc_ == nullptr)
        {
            Drop();
            return;
        }
        enc_size = aes_->Encrypt((unsigned char*)slice_buf_, slice_size, (unsigned char*)slice_buf_enc_);
        data.data = slice_buf_enc_;
        data.size = enc_size;
        /// 生成md5用于校验
        string md5_base64 = OLMD5_base64((unsigned char*)slice_buf_enc_, enc_size);
        head.set_md5(md5_base64);
    }
    else
    {
        //未加密
        if (!md5_base64s_.empty())
        {
            head.set_md5(md5_base64s_.front());
            md5_base64s_.pop_front();
        }
    }

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
    MessageRes res;
    if (!res.ParseFromArray(msg->data, msg->size))
    {
        cerr << "UploadClient::SendSliceRes" << endl;
        Drop();
        return;
    }

    if (res.return_() == MessageRes::ERROR)
    {
        cerr << "UploadClient::SendSliceRes desc: " << res.desc() << endl;
        iFileManager::GetInstance()->FileCheck(1, false);
        Drop();
        return;
    }

    SendSlice();
}

void UploadClient::UploadFileEndRes(msg::MsgHead* head, Msg* msg)
{
    cout << "UploadClient::UploadFileEndRes" << endl;
    //任务完成刷新界面
    iFileManager::GetInstance()->RefreshDir();
    iFileManager::GetInstance()->UploadEnd(task_id);
    Drop();
}

void UploadClient::Drop()
{
    begin_send_data_size_ = -1;
    ifs_.close();
    ClearTimer();
    Close();
    DropInMsg();
}

void UploadClient::TimerCallback()
{
    if (begin_send_data_size_ < 0)
    {
        return;
    }

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
    //不是16的倍数要补全，所以要多预留空间
    slice_buf_enc_ = new char[FILE_SLICE_BYTE + 16];
}

UploadClient::~UploadClient()
{
    delete[] slice_buf_;
    slice_buf_ = nullptr;

    delete[] slice_buf_enc_;
    slice_buf_enc_ = NULL;
    if (aes_)
    {
        aes_->Drop();
        aes_ = NULL;
    }
}

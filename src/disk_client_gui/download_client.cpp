#include "download_client.h"
#include "ifile_manager.h"
#include "msg_comm.pb.h"
#include "tools.h"

using namespace std;
using namespace disk;
using namespace msg;

DownloadClient::DownloadClient()
{
    set_service_name(DOWNLOAD_NAME);
}

DownloadClient::~DownloadClient()
{
}

bool DownloadClient::set_file_info(disk::FileInfo& file)
{
    this->file_ = file;
    if (file.filedir() == "")
        file_.set_filedir("");
    
    local_path_ = file.local_path();
    ofs_.open(file.local_path(), ios::binary);
    if (!ofs_.is_open())
    {
        cout << "set_file " << file.local_path() << " failed!" << endl;
        return false;
    }
    return true;
}

void DownloadClient::ConnectCallback()
{
    cout << "DownloadClient::ConnectCallback" << endl;
    SendMsg((MsgType)DOWNLOAD_FILE_REQ, &file_);
}

void DownloadClient::RegisterMsgCallback()
{
    RegisterCallback((MsgType)DOWNLOAD_FILE_RES, (MsgCBFunc)&DownloadClient::DownloadFileRes);
    RegisterCallback((MsgType)DOWNLOAD_SLICE_REQ, (MsgCBFunc)&DownloadClient::DownloadSliceReq);
}

void DownloadClient::DownloadFileRes(msg::MsgHead* head, Msg* msg)
{
    if (!file_.ParseFromArray(msg->data, msg->size))
    {
        cout << "XDownloadClient::DownloadFileRes ParseFromArray failed!" << endl;
        return;
    }

    //文件加密，需要有秘钥
    if (file_.is_enc())
    {
        auto pass = iFileManager::GetInstance()->password();
        if (pass.empty())
        {
            cout << "please set password" << endl;
            //具体的提示的语言，可以根据字符串替换为不同的语言
            iFileManager::GetInstance()->ErrorSig("该文件为加密文件，请输入密钥后下载!");
            Drop();
            DelFile(local_path_, false);
            return;
        }
        aes_ = OLAES::Create();
        aes_->SetKey(pass.c_str(), pass.size(), false);
    }

    /// 如果是加密文件需要验证加密
    int task_id = iFileManager::GetInstance()->AddDownloadTask(file_);
    task_id_ = task_id;

    SendMsg((MsgType)DOWNLOAD_FILE_BEGTIN, &file_);

    begin_recv_data_size_ = recv_data_size();
    iFileManager::GetInstance()->DownloadProcess(task_id, 0);
}

void DownloadClient::DownloadSliceReq(msg::MsgHead* head, Msg* msg)
{
    int readed = file_.net_size() + msg->size;
    file_.set_net_size(readed);
    const char* data = msg->data;
    int size = msg->size;

    if (file_.is_enc())
    {
        char* dec_data = new char[size];
        size = aes_->Decrypt((unsigned char*)msg->data, msg->size, (unsigned char*)dec_data);
        if (size <= 0)
        {
            cerr << "aes_->Decrypt failed!" << endl;
            delete dec_data;
            Drop();
			DelFile(local_path_, false);
            return;
        }
        /// 还原原始数据大小
        if (readed > file_.ori_size())
        {
            size = size - (readed - file_.ori_size());
        }
        data = dec_data;
    }


    string md5_base64 = OLMD5_base64((unsigned char*)data, size);
    all_md5_base64_ += md5_base64;

    ofs_.write(data, size);
    if (file_.is_enc())
    {
        delete data;
    }

    SendMsg((MsgType)DOWNLOAD_SLICE_RES, &file_);

    /// 文件接收结束 
    if (file_.filesize() == file_.net_size())
    {
        iFileManager::GetInstance()->DownloadEnd(task_id_);

        //校验整个文件的md5
        string file_md5 = OLMD5_base64((unsigned char*)all_md5_base64_.data(), all_md5_base64_.size());
        if (file_md5 != file_.md5())
        {
            cerr << "file is not complete" << endl;
            iFileManager::GetInstance()->FileCheck(2, false);
	    Drop();
	    DelFile(local_path_, false);
	    return;
        }

        Drop();
    }
}

void DownloadClient::Drop()
{
    ofs_.close();
    ClearTimer();
    Close();
}

void DownloadClient::TimerCallback()
{
    if (begin_recv_data_size_ < 0)
        return;

    /// 已发送的数据
    long long recved = recv_data_size() - begin_recv_data_size_;

    iFileManager::GetInstance()->DownloadProcess(task_id_, recved);
}




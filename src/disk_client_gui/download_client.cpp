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
        file_.set_is_dir("");
    
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

    ofs_.write(data, size);

    SendMsg((MsgType)DOWNLOAD_SLICE_RES, &file_);

    /// 文件接收结束 
    if (file_.filesize() == file_.net_size())
    {
        iFileManager::GetInstance()->DownloadEnd(task_id_);
        //校验整个文件的md5
        ofs_.close();

        ClearTimer();
        Close();
    }
}

void DownloadClient::TimerCallback()
{
    if (begin_recv_data_size_ < 0)
        return;

    /// 已发送的数据
    long long recved = recv_data_size() - begin_recv_data_size_;

    iFileManager::GetInstance()->DownloadProcess(task_id_, recved);
}




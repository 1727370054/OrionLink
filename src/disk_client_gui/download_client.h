#ifndef DOWNLOAD_CLIENT_H
#define DOWNLOAD_CLIENT_H

#include "service_client.h"
#include "disk_client_gui.pb.h"

#include <fstream>

class OLAES;

class DownloadClient : public ServiceClient
{
public:
    ~DownloadClient();

    static DownloadClient* Create()
    {
        DownloadClient* download_client = new DownloadClient();
        download_client->set_auto_delete(false);
        download_client->set_auto_connect(false);
        download_client->set_timer_ms(100);
        return download_client;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 客户端连接成功的回调，开始发送下载文件的请求
    virtual void ConnectCallback() override;

    virtual void TimerCallback() override;

    static void RegisterMsgCallback();

    void DownloadFileRes(msg::MsgHead* head, Msg* msg);

    void DownloadSliceReq(msg::MsgHead* head, Msg* msg);

    void Drop();

    bool set_file_info(disk::FileInfo& file);
private:
    DownloadClient();
    DownloadClient(const DownloadClient&) = delete;
    DownloadClient& operator=(const DownloadClient&) = delete;
private:
    int task_id_ = 0;

    disk::FileInfo file_;
    std::ofstream ofs_;

    /// 开始发送数据时，已经发送的值，要确保缓冲已经都发送成功
    long long begin_recv_data_size_ = -1;

    std::string all_md5_base64_ = "";
    //加密文件用
    OLAES* aes_ = 0;
};

#endif // DOWNLOAD_CLIENT_H


#ifndef UPLOAD_CLIENT_H
#define UPLOAD_CLIENT_H

#include "service_client.h"
#include "ssl_ctx.h"
#include "disk_client_gui.pb.h"

#include <fstream>

/// 每个文件创建一个upload对象

class UploadClient : public ServiceClient
{
public:
    ~UploadClient();

    static UploadClient* Create()
    {
        UploadClient* upload_client = new UploadClient();
        upload_client->set_auto_delete(false);
        upload_client->set_auto_connect(false);
        upload_client->set_timer_ms(100);
       /* SSLCtx* ssl_ctx_ = new SSLCtx();
        ssl_ctx_->InitClient();
        upload_client->set_ssl_ctx(ssl_ctx_);*/
        return upload_client;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 客户端连接成功的回调，开始发送上传文件的请求
    virtual void ConnectCallback() override;

    static void RegisterMsgCallback();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收到服务端上传文件的响应, 开始发送文件片
    void UploadFileRes(msg::MsgHead* head, Msg* msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收到服务端上传文件片的响应, 再次发送文件片
    void SendSliceRes(msg::MsgHead* head, Msg* msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收到服务端上传文件结束的响应
    void UploadFileEndRes(msg::MsgHead* head, Msg* msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 定时器回调函数，通过定时器跟踪进度
    virtual void TimerCallback() override;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 
    bool set_file_info(disk::FileInfo file_info);

    int task_id = 0;
private:
    void SendSlice();

    UploadClient();
    UploadClient(const UploadClient&) = delete;
    UploadClient& operator=(const UploadClient&) = delete;
private:
    disk::FileInfo file_info_;

    std::ifstream ifs_;

    /// 文件片缓存
    char* slice_buf_ = nullptr;

    /// 开始发送数据时，已经发送的值，要确保缓冲已经都发送成功
    long long begin_send_data_size_ = -1;
};

#endif // UPLOAD_CLIENT_H


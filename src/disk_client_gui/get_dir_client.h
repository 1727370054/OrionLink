#ifndef GET_DIR_CLIENT_H
#define GET_DIR_CLIENT_H

#include "service_client.h"
#include "ssl_ctx.h"
#include "disk_client_gui.pb.h"

#include <chrono>

class GetDirClient : public ServiceClient
{
public:
    ~GetDirClient();

    static GetDirClient* GetInstance()
    {
        static GetDirClient get_dir_client;
        get_dir_client.set_auto_delete(false);
        SSLCtx* ssl_ctx_ = new SSLCtx();
        ssl_ctx_->InitClient();
        get_dir_client.set_ssl_ctx(ssl_ctx_);
        return &get_dir_client;
    }

    static void RegisterMsgCallback();

    void GetDirReq(disk::GetDirReq& req);

    void GetDirRes(msg::MsgHead *head, Msg *msg);

    void NewDirReq(std::string path);

    void NewDirRes(msg::MsgHead* head, Msg* msg);

    void DeleteFileReq(disk::FileInfo& file_info);

    void DeleteFileRes(msg::MsgHead* head, Msg* msg);

    void GetDiskInfoReq();

    void GetDiskInfoRes(msg::MsgHead* head, Msg* msg);

    //定时器获取上传和下载服务器列表
    virtual void TimerCallback() override;

    /// @brief 获取上传和下载的服务器列表
    void GetService();

    void GetServiceRes(msg::MsgHead* head,Msg* msg);
private:
    GetDirClient();
    GetDirClient(const GetDirClient&) = delete;
    GetDirClient& operator=(const GetDirClient&) = delete;
private:
    std::string cur_dir_ = "";
    std::chrono::steady_clock::time_point last_exec_time_;
};

#endif // GET_DIR_CLIENT_H


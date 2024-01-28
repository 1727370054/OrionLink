#ifndef GET_DIR_CLIENT_H
#define GET_DIR_CLIENT_H

#include "service_client.h"
#include "ssl_ctx.h"
#include "disk_client_gui.pb.h"

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

    void GetDirReq(disk::GetDirReq req);

    void GetDirRes(msg::MsgHead *head, Msg *msg);

    void NewDirReq(std::string path);

    void NewDirRes(msg::MsgHead* head, Msg* msg);
private:
    GetDirClient();
    GetDirClient(const GetDirClient&) = delete;
    GetDirClient& operator=(const GetDirClient&) = delete;
private:
    std::string cur_dir_ = "";
};

#endif // GET_DIR_CLIENT_H


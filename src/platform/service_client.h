#ifndef SERVICE_CLIENT_H
#define SERVICE_CLIENT_H

#include "msg_event.h"
#include "thread_pool.h"

class XCOM_API ServiceClient : public MsgEvent
{
public:
    ServiceClient();
    ~ServiceClient();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 将任务加入到线程池中，进行连接，调用的是 ComTask 类的 Init 进行连接
    virtual void StartConnect();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送消息，组装头部(添加token和微服务名称)
    /// @param type 消息类型
    /// @param message 结构化的消息内容
    /// @return 发送成功返回true，否则相反 (bev可能未设置)
    ///////////////////////////////////////////////////////////////////////////
    bool SendMsg(msg::MsgType type, const google::protobuf::Message* message) override;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 设置头部信息
    void SetHead(msg::MsgHead* head);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 阻塞等待线程退出
    void Wait();

    virtual void set_service_name(std::string service_name) { service_name_ = service_name; }
    virtual void set_login_info(msg::LoginRes* login);
    msg::LoginRes* login_info() { return login_info_; }
private:
    ThreadPool* thread_pool_ = nullptr;
    /// 保存登陆信息
    msg::LoginRes* login_info_ = nullptr;
    std::mutex login_info_mutex_;

    std::string service_name_ = "";
};

#endif // SERVICE_CLIENT_H


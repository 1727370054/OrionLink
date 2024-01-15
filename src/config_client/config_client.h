#ifndef CONFIG_CLIENT_H
#define CONFIG_CLIENT_H

#include "service_client.h"

namespace google
{
    namespace protobuf
    {
        namespace compiler
        {
            class Importer;
            class DiskSourceTree;
        }
    }
}

/// 消息回调函数的消息类型
enum MsgCBType
{
    MSG_SAVE_TYPE = 1,  /// 界面保存配置
    MSG_DEL_TYPE = 2    /// 界面删除配置
};

/// @brief 对配置信息变动的消息回调函数(界面端使用)
typedef void (*ConfigResCBFunc) (MsgCBType type,bool is_ok, const char* desc);
/// @brief 定时器回调函数
typedef void (*ConfigTimerCBFunc) ();

class ConfigClient : public ServiceClient
{
public:
    virtual ~ConfigClient();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 获取单例对象
    static ConfigClient* GetInstance()
    {
        static ConfigClient config_client;
        config_client.set_auto_delete(false);
        return &config_client;
    }

    bool Init() override;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 开始连接配置中心，开启定时器获取配置
    /// @param local_ip 本地IP
    /// @param local_port 本地端口
    /// @param conf_message 配置对象
    /// @param func 定时器回调函数
    /// @return 成功返回true
    bool StartGetConf(const char* local_ip, int local_port,
        google::protobuf::Message* conf_message, ConfigTimerCBFunc func);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 开始连接配置中心，开启定时器获取配置
    /// @param server_ip 配置中心IP
    /// @param server_port 配置中心端口
    /// @param conf_message 配置对象
    /// @param timeout_sec 等待连接配置中心的超时时间
    /// @return 成功返回true
    bool StartGetConf(const char* server_ip, int server_port,
        const char *local_ip, int local_port,
        google::protobuf::Message* conf_message, int timeout_sec = 10);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 定时器回调函数
    virtual void TimerCallback() override;

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 获取下载的本地参数配置信息
    /// @param key 字段名称
    /// @return 成功返回对应配置信息
    int GetInt(const char* key);
    std::string GetString(const char* key);
    bool GetBool(const char* key);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 注册消息处理的回调函数
    static void RegisterMsgCallback();

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送上传配置请求
    /// @param config 配置信息(结构化数据)
    void SendConfigReq(msg::Config *config);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 接收到上传配置的响应
    /// @param head 反序列化头部
    /// @param msg 序列化的消息
    void SendConfigRes(msg::MsgHead* head, Msg* msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送下载配置请求，如果IP为null，则取连接配置中心的地址
    /// @param ip 微服务IP
    /// @param port 微服务端口
    void LoadConfigReq(const char *ip, int port);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 下载配置响应，保存到本地
    /// @param head 反序列化头部
    /// @param msg 序列化的消息
    void LoadConfigRes(msg::MsgHead* head, Msg* msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 获取配置项
    /// @param ip 微服务IP
    /// @param port 微服务端口
    /// @param out_config 存在该配置项，拷贝返回，输出型参数
    /// @param timeout_ms 超时时间(毫秒)
    /// @return 存在返回true，不存在返回false
    ///////////////////////////////////////////////////////////////////////////
    bool GetConfig(const char* ip, int port, msg::Config* out_config, int timeout_ms = 200);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送下载全部配置请求(分页) 1.断开连接自动重连 2.等待结果返回
    /// @param page 页数，从1开始
    /// @param page_count 页显示的记录数量
    /// @param timeout_sec 超时时间
    /// @return 返回微服务列表
    msg::ConfigList GetAllConfig(int page, int page_count, int timeout_sec);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 下载全部配置响应
    /// @param head 反序列化头部
    /// @param msg 序列化的消息
    void LoadAllConfigRes(msg::MsgHead* head, Msg* msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 发送删除配置的请求
    /// @param service_ip 微服务IP
    /// @param service_port 微服务端口
    void DeleteConfigReq(const char *service_ip, int service_port);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 删除配置的响应
    /// @param head 反序列化头部
    /// @param msg 序列化的消息
    void DeleteConfigRes(msg::MsgHead* head, Msg* msg);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 载入proto文件 (线程不安全)
    /// @param filename 文件路径
    /// @param class_name 配置类型 (如果class_name为空，取第一个类型)
    /// @param out_proto_code 返回读取到的代码，包含命名空间和版本
    /// @return 成功返回动态生成的message，失败返回NULL，第二次调用会清理上一次空间
    ///////////////////////////////////////////////////////////////////////////
    google::protobuf::Message* LoadProto(const std::string& filename,
        const std::string& class_name, std::string &out_proto_code);

    ///////////////////////////////////////////////////////////////////////////
    /// @brief 设置当前配置对象
    /// @param message 配置对象
    void SetCurServiceMessage(google::protobuf::Message* message);

    void set_config_res_cb(ConfigResCBFunc func) { ConfigResCB = func; }
private:
    ConfigClient();
    ConfigClient(const ConfigClient&) = delete;
    ConfigClient& operator=(const ConfigClient&) = delete;
private:
    /// 对配置信息变动的消息回调函数(界面端使用)
    ConfigResCBFunc ConfigResCB = nullptr;

    /// 定时器回调函数
    ConfigTimerCBFunc ConfigTimerCB = nullptr;

    /// 本地微服务的IP和端口
    char local_ip_[16] = { 0 };
    int local_port_ = 0;

    /// 动态解析proto文件
    google::protobuf::compiler::Importer* importer_ = nullptr;
    /// 解析文件的管理对象
    google::protobuf::compiler::DiskSourceTree* source_tree_ = nullptr;

    /// 根据proto文件动态加载的message对象
    google::protobuf::Message* dynamic_msg_ = nullptr;
};

#endif // CONFIG_CLIENT_H


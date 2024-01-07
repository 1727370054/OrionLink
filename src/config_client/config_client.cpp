#include "config_client.h"
#include "msg_comm.pb.h"
#include "tools.h"

#include <map>

using namespace msg;
using namespace std;

/// 单例模式锁
std::mutex ConfigClient::mutex_;

/// 存储配置信息 key = ip_port
static map<string, Config> conf_map;
static mutex conf_map_mutex;

/// 存储当前微服务配置
static google::protobuf::Message* cur_service_conf = nullptr;
static mutex cur_service_conf_mutex;

int ConfigClient::GetInt(const char* key)
{
    Mutex lock(&cur_service_conf_mutex);
    if (!key || !cur_service_conf) return 0;
    /// 获取描述对象->获取字段
    auto field = cur_service_conf->GetDescriptor()->FindFieldByName(key);
    if (!field) return 0;

    /// 通过反射对象获取字段信息
    return cur_service_conf->GetReflection()->GetInt32(*cur_service_conf, field);
}

std::string ConfigClient::GetString(const char* key)
{
    Mutex lock(&cur_service_conf_mutex);
    if (!key || !cur_service_conf) return "";
    /// 获取描述对象->获取字段
    auto field = cur_service_conf->GetDescriptor()->FindFieldByName(key);
    if (!field) return "";

    /// 通过反射对象获取字段信息
    return cur_service_conf->GetReflection()->GetString(*cur_service_conf, field);
}

void ConfigClient::SetCurServiceMessage(google::protobuf::Message* message)
{
    Mutex lock(&cur_service_conf_mutex);
    cur_service_conf = message;
}

bool ConfigClient::StartGetConf(const char* server_ip, int server_port, 
    const char* local_ip, int local_port,
    google::protobuf::Message* conf_message, int timeout_sec)
{
    RegisterMsgCallback();
    /// 设置配置中心的IP和端口
    set_server_ip(server_ip);
    set_server_port(server_port);
    StartConnect();
    SetCurServiceMessage(conf_message);

    /// 存储本地微服务IP和端口
    strncpy(local_ip_, local_ip, 16);
    local_port_ = local_port;

    if (!ConfigClient::GetInstance()->WaitConnected(timeout_sec))
    {
        LOGDEBUG("配置中心连接失败");
        return false;
    }
    /// 开启定时器, 设置获取配置定时时间1000毫秒
    SetTimer(3000);
    return true;
}

void ConfigClient::TimerCallback()
{
    /// 定时发出获取配置请求
    if (local_port_ > 0 && local_port_ <= 65535)
        ConfigClient::GetInstance()->LoadConfigReq(local_ip_, local_port_);
}

void ConfigClient::RegisterMsgCallback()
{
    RegisterCallback(MSG_SAVE_CONFIG_RES, (MsgCBFunc)&ConfigClient::RecvConfigRes);
    RegisterCallback(MSG_LOAD_CONFIG_RES, (MsgCBFunc)&ConfigClient::LoadConfigRes);
}

void ConfigClient::SendConfigReq(msg::Config *config)
{
    SendMsg(MSG_SAVE_CONFIG_REQ, config);
}

void ConfigClient::RecvConfigRes(msg::MsgHead* head, Msg* msg)
{
    MessageRes response;
    if (!response.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("ConfigClient::RecvConfigRes failed! ParseFromArray error");
        return;
    }
    if (response.return_() == MessageRes::OK)
    {
        LOGDEBUG("上传配置成功!");
        return;
    }

    stringstream ss;
    ss << "上传配置失败: " << response.desc();
    LOGDEBUG(ss.str().c_str());
}

void ConfigClient::LoadConfigReq(const char* ip, int port)
{
    if (port <= 0 || port > 65535)
    {
        LOGDEBUG("ConfigClient::LoadConfigReq failed! port error");
        return;
    }

    msg::LoadConfigReq request;
    if (ip) /// 如果IP为null，则取连接配置中心的地址
        request.set_service_ip(ip);
    request.set_service_port(port);
    SendMsg(MSG_LOAD_CONFIG_REQ, &request);
}

bool ConfigClient::GetConfig(const char* ip, int port, msg::Config* out_config)
{
    stringstream key;
    key << ip << "_" << port;
    Mutex lock(&conf_map_mutex);
    /// 查找配置
    auto config = conf_map.find(key.str());
    if (config == conf_map.end())
    {
        LOGDEBUG("Can`t find config");
        return false;
    }
    /// 复制配置
    out_config->CopyFrom(config->second);
    return true;
}

void ConfigClient::LoadConfigRes(msg::MsgHead* head, Msg* msg)
{
    Config config;
    if (!config.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("ConfigClient::LoadConfigRes failed! ParseFromArray error");
        return;
    }
    stringstream key;
    key << config.service_ip() << "_" << config.service_port();
    /// 更新配置
    conf_map_mutex.lock();
    conf_map[key.str()] = config;
    conf_map_mutex.unlock();

    /// 存储本地微服务的配置 
    if (local_port_ > 0 && local_port_ <= 65535&& cur_service_conf)
    {
        stringstream local_key;
        local_key << local_ip_ << "_" << local_port_;
        if (key.str() == local_key.str())
        {
            Mutex lock(&cur_service_conf_mutex);
            if (cur_service_conf)
                cur_service_conf->ParseFromString(config.private_pb());
        }
        LOGDEBUG("定时获取配置: " << cur_service_conf->DebugString().c_str());
    }
}

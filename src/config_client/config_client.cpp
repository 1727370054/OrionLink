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
    LOGDEBUG("获取配置请求!");
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
    LOGDEBUG("获取配置响应!");
    Config config;
    if (!config.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("ConfigClient::LoadConfigRes failed! ParseFromArray error");
        return;
    }
    LOGDEBUG(config.DebugString().c_str());
    stringstream key;
    key << config.service_ip() << "_" << config.service_port();
    /// 更新配置
    conf_map_mutex.lock();
    conf_map[key.str()] = config;
    conf_map_mutex.unlock();
}

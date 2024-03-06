#include "log_client.h"
#include "config_client.h"
#include "msg_comm.pb.h"
#include "tools.h"

#include <map>
#include <thread>
#include <fstream>
#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/dynamic_message.h>

#define PB_ROOT "root/"

using namespace msg;
using namespace std;
using namespace google;

/// 存储配置信息 key = ip_port
static map<string, Config> conf_map;
static mutex conf_map_mutex;

/// 存储当前微服务配置
static google::protobuf::Message *cur_service_conf = nullptr;
static mutex cur_service_conf_mutex;

/// 存储获取的全部微服务配置列表
static ConfigList *all_config = nullptr;
static mutex all_config_mutex;

void ConfigClient::RegisterMsgCallback()
{
    RegisterCallback(MSG_SAVE_CONFIG_RES, (MsgCBFunc)&ConfigClient::SendConfigRes);
    RegisterCallback(MSG_LOAD_CONFIG_RES, (MsgCBFunc)&ConfigClient::LoadConfigRes);
    RegisterCallback(MSG_LOAD_ALL_CONFIG_RES, (MsgCBFunc)&ConfigClient::LoadAllConfigRes);
    RegisterCallback(MSG_DEL_CONFIG_RES, (MsgCBFunc)&ConfigClient::DeleteConfigRes);
}

int ConfigClient::GetInt(const char *key)
{
    Mutex lock(&cur_service_conf_mutex);
    if (!key || !cur_service_conf)
        return 0;
    /// 获取描述对象->获取字段
    auto field = cur_service_conf->GetDescriptor()->FindFieldByName(key);
    if (!field)
        return 0;

    /// 通过反射对象获取字段信息
    return cur_service_conf->GetReflection()->GetInt32(*cur_service_conf, field);
}

std::string ConfigClient::GetString(const char *key)
{
    Mutex lock(&cur_service_conf_mutex);
    if (!key || !cur_service_conf)
        return "";
    /// 获取描述对象->获取字段
    auto field = cur_service_conf->GetDescriptor()->FindFieldByName(key);
    if (!field)
        return "";

    /// 通过反射对象获取字段信息
    return cur_service_conf->GetReflection()->GetString(*cur_service_conf, field);
}

bool ConfigClient::GetBool(const char *key)
{
    Mutex lock(&cur_service_conf_mutex);
    if (!key || !cur_service_conf)
        return false;
    /// 获取描述对象->获取字段
    auto field = cur_service_conf->GetDescriptor()->FindFieldByName(key);
    if (!field)
        return false;

    /// 通过反射对象获取字段信息
    return cur_service_conf->GetReflection()->GetBool(*cur_service_conf, field);
}

void ConfigClient::SetCurServiceMessage(google::protobuf::Message *message)
{
    Mutex lock(&cur_service_conf_mutex);
    cur_service_conf = message;
}

bool ConfigClient::Init()
{
    ServiceClient::Init();
    /// 先调用一次定时器，确保消息及时获取
    TimerCallback();
    return true;
}

bool ConfigClient::StartGetConf(const char *local_ip, int local_port,
                                google::protobuf::Message *conf_message, ConfigTimerCBFunc func)
{
    RegisterMsgCallback();
    SetCurServiceMessage(conf_message);
    this->ConfigTimerCB = func;
    /// 存储本地微服务IP和端口
    if (local_ip)
        strncpy(local_ip_, local_ip, 16);
    local_port_ = local_port;

    set_timer_ms(3000);

    /// 读取本地缓存
    stringstream ss;
    ss << local_port_ << "_conf.cache";
    ifstream ifs;
    ifs.open(ss.str(), ios::binary);
    if (!ifs.is_open())
    {
        LOGDEBUG("load local config failed!");
    }
    else
    {
        Mutex lock(&cur_service_conf_mutex);
        if (conf_message)
            cur_service_conf->ParseFromIstream(&ifs);
        ifs.close();
    }

    StartConnect();
    return true;
}

bool ConfigClient::StartGetConf(const char *server_ip, int server_port,
                                const char *local_ip, int local_port,
                                google::protobuf::Message *conf_message, int timeout_sec)
{
    RegisterMsgCallback();
    /// 设置配置中心的IP和端口
    set_server_ip(server_ip);
    set_server_port(server_port);
    SetCurServiceMessage(conf_message);

    StartConnect();

    /// 存储本地微服务IP和端口
    if (local_ip)
        strncpy(local_ip_, local_ip, 16);
    local_port_ = local_port;

    if (!ConfigClient::GetInstance()->WaitConnected(timeout_sec))
    {
        LOGDEBUG("配置中心连接失败");
        return false;
    }

    /// 开启定时器, 设置获取配置定时时间3000毫秒
    SetTimer(3000);
    return true;
}

void ConfigClient::TimerCallback()
{
    if (ConfigTimerCB)
        ConfigTimerCB();
    /// 定时发出获取配置请求
    if (local_port_ > 0 && local_port_ <= 65535)
        ConfigClient::GetInstance()->LoadConfigReq(local_ip_, local_port_);
}

void ConfigClient::SendConfigReq(msg::Config *config)
{
    SendMsg(MSG_SAVE_CONFIG_REQ, config);
}

void ConfigClient::SendConfigRes(msg::MsgHead *head, Msg *msg)
{
    MessageRes response;
    if (!response.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("ConfigClient::SendConfigRes failed! ParseFromArray error");
        if (ConfigResCB)
            ConfigResCB(MSG_SAVE_TYPE, false, "ParseFromArray error");
        return;
    }
    if (response.return_() == MessageRes::OK)
    {
        LOGDEBUG("上传配置成功!");
        if (ConfigResCB)
            ConfigResCB(MSG_SAVE_TYPE, true, "上传配置成功!");
        return;
    }

    stringstream ss;
    ss << "上传配置失败: " << response.desc();
    if (ConfigResCB)
        ConfigResCB(MSG_SAVE_TYPE, false, response.desc().c_str());
    LOGDEBUG(ss.str().c_str());
}

void ConfigClient::LoadConfigReq(const char *ip, int port)
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

void ConfigClient::LoadConfigRes(msg::MsgHead *head, Msg *msg)
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

    /// 没有本地配置
    if (local_port_ <= 0 || !cur_service_conf)
        return;
    string ip = local_ip_;
    if (ip.empty())
    {
        ip = config.service_ip();
    }
    stringstream local_key;
    local_key << ip << "_" << local_port_;
    if (key.str() != local_key.str())
        return;

    Mutex lock(&cur_service_conf_mutex);
    if (!cur_service_conf->ParseFromString(config.private_pb()))
    {
        LOGDEBUG("local config ParseFromString failed!");
        return;
    }
    /// LOGDEBUG("定时获取配置: " << cur_service_conf->DebugString().c_str());
    /// 存储到本地文件
    /// 文件名 [port]_conf.cache  20030_conf.cache
    stringstream ss;
    ss << local_port_ << "_conf.cache";
    ofstream ofs;
    ofs.open(ss.str(), ios::binary);
    if (!ofs.is_open())
    {
        LOGDEBUG("save local config failed!");
        return;
    }
    cur_service_conf->SerializePartialToOstream(&ofs);
    ofs.close();
}

bool ConfigClient::GetConfig(const char *ip, int port, msg::Config *out_config, int timeout_ms)
{
    /// 10毫秒监听一次
    int count = timeout_ms / 10;
    stringstream key;
    key << ip << "_" << port;

    /// 查找配置
    for (int i = 0; i < count; i++)
    {
        Mutex lock(&conf_map_mutex);
        auto config = conf_map.find(key.str());
        if (config == conf_map.end())
        {
            this_thread::sleep_for(10ms);
            continue;
        }
        /// 复制配置
        out_config->CopyFrom(config->second);
        return true;
    }

    LOGDEBUG("Can`t find config");
    return false;
}

msg::ConfigList ConfigClient::GetAllConfig(int page, int page_count, int timeout_sec)
{
    /// 清理历史数据
    {
        Mutex lock(&all_config_mutex);
        delete all_config;
        all_config = nullptr;
    }

    msg::ConfigList configs;
    /// 断开连接，自动重连
    if (!AutoConnect(timeout_sec))
        return configs;
    /// 发送获取微服务配置列表的消息
    LoadAllConfigReq request;
    request.set_page(page);
    request.set_page_count(page_count);
    SendMsg(MSG_LOAD_ALL_CONFIG_REQ, &request);

    /// 等待服务器响应, 10ms监听一次
    int count = timeout_sec * 100;
    for (int i = 0; i < count; i++)
    {
        {
            Mutex lock(&all_config_mutex);
            if (all_config)
            {
                return *all_config;
            }
        }
        this_thread::sleep_for(10ms);
    }

    return configs;
}

void ConfigClient::LoadAllConfigRes(msg::MsgHead *head, Msg *msg)
{
    Mutex lock(&all_config_mutex);
    if (!all_config)
        all_config = new ConfigList();
    if (!all_config->ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("ConfigClient::LoadAllConfigRes failed! ParseFromArray error");
        return;
    }
}

void ConfigClient::DeleteConfigReq(const char *service_ip, int service_port)
{
    if (!service_ip || strlen(service_ip) == 0 || service_port < 0 || service_port > 65535)
    {
        LOGDEBUG("ConfigClient::DeleteConfigReq failed! ip or port error");
        return;
    }
    msg::LoadConfigReq request;
    request.set_service_ip(service_ip);
    request.set_service_port(service_port);
    SendMsg(MSG_DEL_CONFIG_REQ, &request);
}

void ConfigClient::DeleteConfigRes(msg::MsgHead *head, Msg *msg)
{
    MessageRes response;
    if (!response.ParseFromArray(msg->data, msg->size))
    {
        LOGDEBUG("ConfigClient::DeleteConfigRes failed! ParseFromArray error");
        if (ConfigResCB)
            ConfigResCB(MSG_DEL_TYPE, false, "ParseFromArray error");
        return;
    }
    if (response.return_() == MessageRes::OK)
    {
        LOGDEBUG("删除配置成功!");
        if (ConfigResCB)
            ConfigResCB(MSG_DEL_TYPE, true, "删除配置成功!");
        return;
    }

    stringstream ss;
    ss << "删除配置失败: " << response.desc();
    if (ConfigResCB)
        ConfigResCB(MSG_DEL_TYPE, false, response.desc().c_str());
    LOGDEBUG(ss.str().c_str());
}

/// 显示解析的语法错误
class ConfigError : public protobuf::compiler::MultiFileErrorCollector
{
public:
    virtual void AddError(const std::string &filename, int line, int column,
                          const std::string &message)
    {
        stringstream ss;
        ss << filename << "|" << line << "|" << column << " " << message;
        LOGDEBUG(ss.str().c_str());
    }
};

static ConfigError config_error;

protobuf::Message *ConfigClient::LoadProto(const string &filename,
                                           const string &class_name, string &out_proto_code)
{
    /// 需要清理空间
    delete importer_;
    importer_ = nullptr;
    importer_ = new protobuf::compiler::Importer(source_tree_, &config_error);
    if (!importer_)
        return NULL;
    /// 加载proto文件
    string path = PB_ROOT;
    path += filename;
    /// 返回文件描述符
    auto file_desc = importer_->Import(path);
    if (!file_desc)
        return NULL;
    stringstream ss;
    ss << filename << " load success!";
    LOGDEBUG(ss.str().c_str());

    /// 获取消息类型描述符
    /// 如果class_name为空，取第一个类型
    const protobuf::Descriptor *message_desc = nullptr;
    if (class_name.empty())
    {
        if (file_desc->message_type_count() <= 0)
        {
            LOGDEBUG("proto file not message");
            return NULL;
        }
        /// 取第一个类型
        message_desc = file_desc->message_type(0);
    }
    else
    {
        /// 查找类型 命名空间问题 msg.DirReq

        /// 包含命名空间的类名
        string class_name_package = "";

        /// 没有包含命名空间
        if (class_name.find('.') == string::npos)
        {
            if (file_desc->package().empty()) /// proto文件是否有命名空间
            {
                class_name_package = class_name;
            }
            else
            {
                class_name_package = file_desc->package();
                class_name_package += ".";
                class_name_package += class_name;
            }
        }
        else
        {
            class_name_package = class_name;
        }
        message_desc = file_desc->pool()->FindMessageTypeByName(class_name_package);
    }
    if (!message_desc)
    {
        LOGDEBUG("proto文件没有指定的消息类型");
        return NULL;
    }
    LOGDEBUG(message_desc->DebugString().c_str());

    /// 反射生成message对象
    /// 清理上一次对象
    delete dynamic_msg_;
    dynamic_msg_ = nullptr;
    /// 动态创建一个消息类型的工厂，不能销毁，不然消息原型会失效
    static protobuf::DynamicMessageFactory factory;
    /// 创建消息原型
    auto message = factory.GetPrototype(message_desc);
    dynamic_msg_ = message->New();

    /*
     *  syntax = "proto3";	// 版本号
     *  package msg;		    // 命名空间
     *  message DirReq
     *  {
     *      string path = 1;
     *  }
     */
    /// syntax = "proto3";
    out_proto_code = "syntax =\"";
    out_proto_code += file_desc->SyntaxName(file_desc->syntax());
    out_proto_code += "\";\n";
    /// package msg;
    out_proto_code += "package ";
    out_proto_code += file_desc->package();
    out_proto_code += ";\n";
    /// 存放枚举类型(暂时不支持多文件 import)
    /// 存在多个字段同一个枚举类型(同一个类型，只生成同一个代码)
    map<string, const protobuf::EnumDescriptor *> enum_desc;
    for (int i = 0; i < message_desc->field_count(); i++)
    {
        auto field = message_desc->field(i);
        if (field->type() != protobuf::FieldDescriptor::TYPE_ENUM)
        {
            continue;
        }
        string enum_name = field->enum_type()->name();
        if (enum_desc.find(enum_name) == enum_desc.end()) /// 没有添加过
        {
            out_proto_code += field->enum_type()->DebugString() + "\n";
            enum_desc[enum_name] = field->enum_type();
        }
    }

    /// message DirReq
    out_proto_code += message_desc->DebugString();

    return dynamic_msg_;
}

ConfigClient::ConfigClient()
{
    set_service_name(CONFIG_NAME);
    source_tree_ = new protobuf::compiler::DiskSourceTree();
    source_tree_->MapPath("", "");
    /// 使用绝对路径不加root会失败
    source_tree_->MapPath(PB_ROOT, "");
}

ConfigClient::~ConfigClient()
{
}

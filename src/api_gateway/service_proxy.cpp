#include "service_proxy.h"
#include "msg_comm.pb.h"
#include "tools.h"

#include <thread>

using namespace std;
using namespace msg;

ServiceProxy::ServiceProxy()
{
}

ServiceProxy::~ServiceProxy()
{
}

bool ServiceProxy::Init()
{
    /// 1.��ע�����Ļ�ȡ΢�����б�

    ///////////////////��������/////////////////////////
    ServiceMap service_map;
    auto service_map_ptr = service_map.mutable_service_map();
    ServiceMap::ServiceList list;
    {
        auto service = list.add_service();
        service->set_name("dir");
        service->set_ip("127.0.0.1");
        service->set_port(9999);
        (*service_map_ptr)["dir"] = list;
    }
    {
        auto service = list.add_service();
        service->set_name("dir");
        service->set_ip("127.0.0.1");
        service->set_port(10000);
        (*service_map_ptr)["dir"] = list;
    }
    {
        auto service = list.add_service();
        service->set_name("dir");
        service->set_ip("127.0.0.1");
        service->set_port(10001);
        (*service_map_ptr)["dir"] = list;
    }

    cout << service_map.DebugString() << endl;

    /// 2. ��΢����������
    /// ���� ServiceMap ����
    for (const auto& m : (*service_map_ptr))
    {
        client_map_[m.first] = vector<ServiceProxyClient*>();
        for (const auto& s : m.second.service())
        {
            auto proxy = new ServiceProxyClient();
            proxy->set_server_ip(s.ip().c_str());
            proxy->set_port(s.port());
            proxy->StartConnect();
            client_map_[m.first].push_back(proxy);
            client_map_last_index_[m.first] = 0;
        }
    }

    return true;
}

void ServiceProxy::DeleteEvent(MsgEvent* event)
{
    if (!event) return;
    Mutex lock(&callbacks_mutex_);
    auto call = callbacks_.find(event);
    if (call == callbacks_.end())
    {
        LOGERROR("Delete event failed, not find");
        return;
    }
    call->second->DeleteEvent(event);
}

bool ServiceProxy::SendMsg(msg::MsgHead* head, Msg* msg, MsgEvent* event)
{
    /// 1. ���ؾ����ҵ�΢���������

    if (!head || !msg) return false;
    string service_name = head->service_name();
    auto client_list = client_map_.find(service_name);
    if (client_list == client_map_.end())
    {
        stringstream ss;
        ss << service_name << " client_map_ not find";
        LOGDEBUG(ss.str().c_str());
        return false;
    }

    /// ��ѯ�ҵ���һ�ε�΢��������
    int cur_index = client_map_last_index_[service_name];
    int list_size = client_list->second.size();
    for (int i = 0; i < list_size; i++)
    {
        cur_index++;
        cur_index = cur_index % list_size;
        client_map_last_index_[service_name] = cur_index;
        auto client = client_list->second[cur_index];
        if (client->is_connected())
        {
            /// �����˳�����
            {
                Mutex lock(&callbacks_mutex_);
                callbacks_[event] = client;
            }

            /// ת����Ϣ��΢����
            return client->SendMsg(head, msg, event);
        }
    }
    LOGDEBUG("can't find proxy");
    return false;
}

void ServiceProxy::Start()
{
    thread th(&ServiceProxy::Main, this);
    th.detach();
}

void ServiceProxy::Stop()
{
    is_exit_ = true;
}

void ServiceProxy::Main()
{
    while (!is_exit_)
    {
        /// ��ע�����Ļ�ȡ ΢�����б�ĸ���
        /// ��ʱȫ�����»�ȡ
        for (const auto & m : client_map_)
        {
            for (const auto& c : m.second)
            {
                if (c->is_connected())
                    continue;
                if (!c->is_connecting())
                {
                    c->Connect();
                }
            }
        }
        this_thread::sleep_for(3000ms);
    }
}




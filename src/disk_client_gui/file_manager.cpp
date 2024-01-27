#include "file_manager.h"
#include "get_dir_client.h"
#include "disk_client_gui.pb.h"

using namespace std;
using namespace msg;
using namespace disk;

void FileManager::GetDir(std::string root)
{
    GetDirReq req;
    req.set_root(root);
    GetDirClient::GetInstance()->GetDirReq(req);
}

FileManager::FileManager()
{
    instance_ = this;
    GetDirClient::RegisterMsgCallback();
    GetDirClient::GetInstance()->set_server_ip("127.0.0.1");
    GetDirClient::GetInstance()->set_server_port(DIR_PORT);
    this_thread::sleep_for(3000ms);
    GetDirClient::GetInstance()->StartConnect();
}

FileManager::~FileManager()
{
}

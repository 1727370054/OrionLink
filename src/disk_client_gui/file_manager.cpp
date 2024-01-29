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

void FileManager::InitFileManager(std::string server_ip, int server_port)
{
    GetDirClient::RegisterMsgCallback();
    GetDirClient::GetInstance()->set_server_ip(server_ip.c_str());
    GetDirClient::GetInstance()->set_server_port(server_port);
    GetDirClient::GetInstance()->StartConnect();
}

void FileManager::set_login_info(msg::LoginRes login)
{
    GetDirClient::GetInstance()->set_login_info(&login);
    iFileManager::set_login_info(login);
}

void FileManager::NewDir(std::string path)
{
    GetDirClient::GetInstance()->NewDirReq(path);
}

void FileManager::DeleteFile(disk::FileInfo file_info)
{
    GetDirClient::GetInstance()->DeleteFileReq(file_info);
}

FileManager::FileManager()
{
    instance_ = this;
}

FileManager::~FileManager()
{
}

#include "file_manager.h"
#include "upload_client.h"
#include "download_client.h"
#include "get_dir_client.h"
#include "disk_client_gui.pb.h"
#include "log_client.h"
#include "tools.h"

using namespace std;
using namespace msg;
using namespace disk;

void FileManager::GetDir(std::string& root)
{
    GetDirReq req;
    req.set_root(root);
    root_ = root;
    GetDirClient::GetInstance()->GetDirReq(req);
}

void FileManager::InitFileManager(std::string server_ip, int server_port)
{
    GetDirClient::RegisterMsgCallback();
    UploadClient::RegisterMsgCallback();
    DownloadClient::RegisterMsgCallback();

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

void FileManager::DeleteFile(disk::FileInfo& file_info)
{
    GetDirClient::GetInstance()->DeleteFileReq(file_info);
}

void FileManager::UploadFile(disk::FileInfo& file_info)
{
    string ip = GetHostByName(OL_GATEWAY_SERVER_NAME);
    int port = UPLOAD_PORT;

    auto services = upload_servers();
    /// 轮询使用服务器
    if (services.services().size() > 0)
    {
        static int index = 0;
        index = index % services.services().size();
        ip = services.services().at(index).ip();
        port = services.services().at(index).port();
        index++;
    }
    stringstream ss;
    ss << "upload server " << ip << ":" << port;
    LOGINFO(ss.str().c_str());

    ifstream ifs(file_info.local_path(), ios::ate);
    if (!ifs)
    {
        cout << "UploadFile failed!" << file_info.local_path() << endl;
        return;
    }
    long long file_size = ifs.tellg();
    ifs.close();
    file_info.set_filesize(file_size);

    auto pass = password();
    if (!pass.empty())
    {
        file_info.set_is_enc(true);
        file_info.set_password(pass);
    }

    auto upload_client = UploadClient::Create();
    if (upload_client == nullptr) return;
    upload_client->set_login_info(&login_info());
    upload_client->set_file_info(file_info);

    upload_client->set_server_ip(ip.c_str());
    upload_client->set_server_port(port);

    upload_client->StartConnect();
    int task_id = AddUploadTask(file_info);
    upload_client->task_id = task_id;
}

void FileManager::DownloadFile(disk::FileInfo& file_info)
{
    string ip = GetHostByName(OL_GATEWAY_SERVER_NAME);
    int port = DOWNLOAD_PORT;

    auto services = download_servers();
    /// 轮询使用服务器
    if (services.services().size() > 0)
    {
        static int index = 0;
        index = index % services.services().size();
        ip = services.services().at(index).ip();
        port = services.services().at(index).port();
        index++;
    }
    stringstream ss;
    ss << "upload server " << ip << ":" << port;
    LOGINFO(ss.str().c_str());

    auto client = DownloadClient::Create();
    if (client == nullptr) return;

    client->set_server_ip(ip.c_str());
    client->set_server_port(port);
    client->set_file_info(file_info);
    auto user = login_info();
    client->set_login_info(&user);
    client->StartConnect();
}

void FileManager::Rename(std::string& old_filename, std::string& new_filename)
{
    GetDirClient::GetInstance()->RenameReq(old_filename, new_filename);
}

FileManager::FileManager()
{
    instance_ = this;
}

FileManager::~FileManager()
{
}

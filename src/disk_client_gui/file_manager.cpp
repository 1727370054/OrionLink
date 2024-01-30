#include "file_manager.h"
#include "upload_client.h"
#include "get_dir_client.h"
#include "disk_client_gui.pb.h"
#include "tools.h"

using namespace std;
using namespace msg;
using namespace disk;

void FileManager::GetDir(std::string root)
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

void FileManager::UploadFile(disk::FileInfo file_info)
{
    string ip = "127.0.0.1";
    int port = UPLOAD_PORT;

    ifstream ifs(file_info.local_path(), ios::ate);
    if (!ifs)
    {
        cout << "UploadFile failed!" << file_info.local_path() << endl;
        return;
    }
    long long file_size = ifs.tellg();
    ifs.close();
    file_info.set_filesize(file_size);

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

FileManager::FileManager()
{
    instance_ = this;
}

FileManager::~FileManager()
{
}

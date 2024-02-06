#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "ifile_manager.h"

class FileManager : public iFileManager
{
public:
    FileManager();
    ~FileManager();

    virtual void GetDir(std::string& root) override;

    virtual void InitFileManager(std::string server_ip, int server_port) override;

    virtual void set_login_info(msg::LoginRes login) override;

    virtual void NewDir(std::string path) override;

    virtual void DeleteFile(disk::FileInfo& file_info) override;

    virtual void UploadFile(disk::FileInfo& file_info) override;

    virtual void DownloadFile(disk::FileInfo& file_info) override;

    virtual void Rename(std::string& old_filename, std::string& new_filename) override;
};

#endif // FILE_MANAGER_H


#ifndef IFILE_MANAGER_H
#define IFILE_MANAGER_H

#include <QObject>
#include <list>

#include "disk_client_gui.pb.h"
#include "msg_comm.pb.h"

class iFileManager  : public QObject
{
    Q_OBJECT

public:
    static iFileManager* GetInstance()
    {
        return instance_;
    }

    iFileManager(QObject *parent = 0);
    ~iFileManager();

    virtual void GetDir(std::string& root) = 0;

    void RefreshDir() { GetDir(root_); }

    virtual void InitFileManager(std::string server_ip, int server_port) = 0;

    virtual void NewDir(std::string path) = 0;

    virtual void DeleteFile(disk::FileInfo& file_info) = 0;

    virtual void UploadFile(disk::FileInfo& file_info) = 0;
    /// 进度从0~1000
    /// 更新上传列表进度 线程安全
    virtual void UploadProcess(int task_id, int sended);
    virtual void UploadEnd(int task_id);

    virtual void DownloadFile(disk::FileInfo& file_info) = 0;
    virtual void DownloadProcess(int task_id, int recved);
    virtual void DownloadEnd(int task_id);

    /// @brief 返回任务ID
    int AddUploadTask(disk::FileInfo file_info);
    int AddDownloadTask(disk::FileInfo file_info);

    virtual void set_login_info(msg::LoginRes login) { login_info_ = login; }
    msg::LoginRes login_info() { return login_info_; }

    void set_upload_servers(msg::ServiceList servers);
    msg::ServiceList upload_servers();
    void set_download_servers(msg::ServiceList servers);
    msg::ServiceList download_servers();
signals:
    void RefreshData(disk::FileInfoList file_list, std::string cur_dir);

    void RefreshDiskInfo(disk::DiskInfo info);
    void RefreshUploadTask(std::list<disk::FileTask> file_list);
    void RefreshDownloadTask(std::list<disk::FileTask> file_list);

protected:
    static iFileManager* instance_;
    msg::LoginRes login_info_;
    std::string root_ = "";

    std::list<disk::FileTask> uploads_;
    std::mutex uploads_mutex_;
    std::list<disk::FileTask> downloads_;
    std::mutex downloads_mutex_;

    /// 上传的服务器列表
    std::mutex servers_mutex_;
    msg::ServiceList upload_servers_;

    /// 下载的服务器列表
    msg::ServiceList download_servers_;
};

#endif // IFILE_MANAGER_H

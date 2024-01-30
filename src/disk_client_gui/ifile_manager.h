﻿#ifndef IFILE_MANAGER_H
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

    virtual void GetDir(std::string root) = 0;

    void RefreshDir() { GetDir(root_); }

    virtual void InitFileManager(std::string server_ip, int server_port) = 0;

    virtual void NewDir(std::string path) = 0;

    virtual void DeleteFile(disk::FileInfo file_info) = 0;

    virtual void UploadFile(disk::FileInfo file_info) = 0;

    /// 进度从0~1000
    /// 更新上传列表进度 线程安全
    virtual void UploadProcess(int task_id, int sended);
    virtual void UploadEnd(int task_id);

    /// @brief 返回任务ID
    int AddUploadTask(disk::FileInfo file_info);

    virtual void set_login_info(msg::LoginRes login) { login_info_ = login; }
    msg::LoginRes login_info() { return login_info_; }
signals:
    void RefreshData(disk::FileInfoList file_list, std::string cur_dir);

    void RefreshDiskInfo(disk::DiskInfo info);
    void RefreshUploadTask(std::list<disk::FileTask> file_list);
protected:
    static iFileManager* instance_;
    msg::LoginRes login_info_;
    std::string root_ = "";

    std::list<disk::FileTask> uploads_;
    std::mutex uploads_mutex_;
};

#endif // IFILE_MANAGER_H

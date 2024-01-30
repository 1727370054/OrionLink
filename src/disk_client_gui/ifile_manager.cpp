﻿#include "ifile_manager.h"
#include "disk_client_gui.pb.h"
#include "tools.h"

using namespace std;
using namespace disk;

iFileManager* iFileManager::instance_ = nullptr;

iFileManager::iFileManager(QObject *parent)
    : QObject(parent)
{}

void iFileManager::UploadProcess(int task_id, int sended)
{
    Mutex lock(&uploads_mutex_);
    for (auto up = uploads_.begin(); up != uploads_.end(); up++)
    {
        if (task_id == up->index())
        {
            up->mutable_file()->set_net_size(sended);
        }
    }

    RefreshUploadTask(uploads_);
}

void iFileManager::UploadEnd(int task_id)
{
    Mutex lock(&uploads_mutex_);
    for (auto up = uploads_.begin(); up != uploads_.end(); up++)
    {
        if (task_id == up->index())
        {
            up->set_is_complete(true);
            up->mutable_file()->set_net_size(up->file().filesize());
        }
    }

    RefreshUploadTask(uploads_);
}

int iFileManager::AddUploadTask(disk::FileInfo file_info)
{
    FileTask task;
    auto file = new FileInfo();
    file->CopyFrom(file_info);
    /// 只能用动态分配的空间，会在task 引用计数为0清理时delete
    task.set_allocated_file(file);
    static int task_id = 0;
    task_id++;
    task.set_index(task_id);
    task.set_tasktime(GetCurTime(time(0)));
    
    {
        Mutex lock(&uploads_mutex_);
        uploads_.push_back(task);
    }

    UploadProcess(task_id, 0);
    return task_id;
}

iFileManager::~iFileManager()
{}

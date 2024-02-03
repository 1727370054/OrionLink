#ifndef TASK_LIST_GUI_H
#define TASK_LIST_GUI_H

#include <QWidget>
#include <list>

#include "disk_client_gui.pb.h"

namespace Ui {
    class TaskListGUI;
}

class TaskListGUI  : public QWidget
{
    Q_OBJECT

public:
    explicit TaskListGUI(QWidget*parent = 0);
    ~TaskListGUI();

    void Show();
    void SetDownButtonChecked();
    void SetUpButtonChecked();
public slots:

    void RefreshUploadTask(std::list<disk::FileTask> file_list);
    void RefreshDownloadTask(std::list<disk::FileTask> file_list);
    void RefreshTask(std::list<disk::FileTask> file_list);
    void OkTask();
    void UpTask();
    void DownTask();
private:
    Ui::TaskListGUI* ui;
    std::list<disk::FileTask> upload_list_;
    std::list<disk::FileTask> download_list_;
};

#endif // TASK_LIST_GUI_H

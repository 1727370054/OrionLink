#ifndef TASK_ITEM_GUI_H
#define TASK_ITEM_GUI_H

#include <QWidget>

#include "disk_client_gui.pb.h"
#include "ui_task_item_gui.h"

class TaskItemGUI : public QWidget
{
    Q_OBJECT

public:
    TaskItemGUI(QWidget *parent = Q_NULLPTR);
    ~TaskItemGUI();
    void SetTask(disk::FileTask task);
private:
    disk::FileTask task_;
    Ui::TaskItemGUI* ui;
};

#endif // TASK_ITEM_GUI_H

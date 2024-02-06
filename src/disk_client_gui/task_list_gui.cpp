#include "task_list_gui.h"
#include "task_item_gui.h"
#include "ui_task_list_gui.h"

#include <QMouseevent>
#include <sstream>
#include <map>
#include <thread>

using namespace std;
using namespace disk;

static map<int, TaskItemGUI*> task_items;

static int ok_task_size = 0;

TaskListGUI::TaskListGUI(QWidget*parent)
    : QWidget(parent),
    ui(new Ui::TaskListGUI())
{
    ui->setupUi(this);
}

TaskListGUI::~TaskListGUI()
{}

void TaskListGUI::RefreshUploadTask(std::list<disk::FileTask> file_list)
{
    if (file_list.empty())
        return;
    upload_list_ = file_list;

    stringstream ss;
    ss << "(" << file_list.size() << ")";
    ui->uplabel->setText(ss.str().c_str());

    if (!ui->upButton->isChecked())
        return;
    RefreshTask(file_list);
}

void TaskListGUI::RefreshDownloadTask(std::list<disk::FileTask> file_list)
{
    if (file_list.empty())return;
    download_list_ = file_list;

    stringstream ss;
    ss << "(" << file_list.size() << ")";
    ui->downlabel->setText(ss.str().c_str());

    if (!ui->downButton->isChecked())
        return;
    RefreshTask(file_list);
}

void TaskListGUI::RefreshTask(std::list<disk::FileTask> file_list)
{
    /// 只修改 不清理
    auto tab = ui->tasktableWidget;

    for (auto task : file_list)
    {
        if (task_items.find(task.index()) == task_items.end())
        {
            tab->insertRow(0);
            auto item = new TaskItemGUI();
            item->SetTask(task);
            tab->setCellWidget(0, 0, item);
            tab->update();
            tab->setRowHeight(0, 51);
            task_items[task.index()] = item;
        }
        else
        {
            task_items[task.index()]->SetTask(task);
        }

        if (task.is_complete())
        {
            ok_task_size = download_list_.size();
            ok_task_size += upload_list_.size();
            stringstream ss;
            ss << "(" << ok_task_size << ")";
            ui->oklabel->setText(ss.str().c_str());
        }
    }
}

void TaskListGUI::OkTask()
{
    ui->oklabel->hide();
    ui->downlabel->show();
    ui->uplabel->show();
    auto tab = ui->tasktableWidget;
    task_items.clear();
    while (tab->rowCount() > 0)
    {
        tab->removeRow(0);
    }
    RefreshTask(download_list_);
    task_items.clear();
    RefreshTask(upload_list_);
}

void TaskListGUI::UpTask()
{
    ui->uplabel->hide();
    ui->downlabel->show();
    ui->oklabel->show();
    auto tab = ui->tasktableWidget;
    task_items.clear();
    while (tab->rowCount() > 0)
    {
        tab->removeRow(0);
    }
    RefreshTask(upload_list_);
}

void TaskListGUI::DownTask()
{
    ui->downlabel->hide();
    ui->uplabel->show();
    ui->oklabel->show();
    auto tab = ui->tasktableWidget;
    task_items.clear();
    while (tab->rowCount() > 0)
    {
        tab->removeRow(0);
    }
    RefreshTask(download_list_);
}

void TaskListGUI::Show()
{
    this->show();
    QWidget* p = (QWidget*)this->parent();
    int w = p->width();
    auto tab_pos = ui->tasktableWidget->pos();
    auto size = ui->tasktableWidget->size();

    size.setHeight(p->height() - pos().y());
    size.setWidth(w - tab_pos.x());
    ui->tasktableWidget->resize(size);
}

void TaskListGUI::SetDownButtonChecked()
{
    ui->downButton->setChecked(true);
}

void TaskListGUI::SetUpButtonChecked()
{
    ui->upButton->setChecked(true);
}


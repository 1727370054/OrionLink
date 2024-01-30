#include "task_list_gui.h"
#include "task_item_gui.h"
#include "ui_task_list_gui.h"

#include <QMouseevent>
#include <sstream>
#include <map>

using namespace std;
using namespace disk;

static map<int, TaskItemGUI*> task_items;

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
    stringstream ss;
    ss << "(" << file_list.size() << ")";
    ui->uplabel->setText(ss.str().c_str());

    upload_list_ = file_list;
    if (!ui->upButton->isChecked())
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
    }
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


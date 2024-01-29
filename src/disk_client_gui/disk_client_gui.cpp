#include "disk_client_gui.h"
#include "login_gui.h"
#include "ui_disk_client_gui.h"
#include "message_box.h"
#include "tools.h"

#include <QMouseEvent>
#include <QHBoxLayout>
#include <QMenu>
#include <QLineEdit>

using namespace std;

#define FILE_ICON_PATH ":/XMSDiskClientGui/Resources/img/FileType/Small/"

DiskClientGUI::DiskClientGUI(LoginGUI* login_gui, iFileManager* f, QWidget *parent)
    : QWidget(parent),
    ui(new Ui::DiskClientGUI),
    login_gui_(new LoginGUI())
{
    this->login_gui_ = login_gui;
    set_ifm(f);
    ui->setupUi(this);
    ////去除原窗口边框
    setWindowFlags(Qt::FramelessWindowHint);
    ////隐藏背景，用于圆角
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);

    auto tab = ui->filetableWidget;
    tab->setColumnWidth(0, 40);
    tab->setColumnWidth(1, 400);
    tab->setColumnWidth(2, 150);
    tab->setColumnWidth(3, 120);
    tab->setColumnWidth(4, 95);

    tab->installEventFilter(this);

    qRegisterMetaType<std::string>("std::string");
    qRegisterMetaType<disk::FileInfoList>("disk::FileInfoList");

    ui->username_label->setText(ifm_->login_info().username().c_str());
    connect(ifm_, &iFileManager::RefreshData, this, &DiskClientGUI::RefreshData);
    Refresh();
}

DiskClientGUI::~DiskClientGUI()
{}

void DiskClientGUI::Refresh()
{
    if (!ifm_) return;
    ifm_->GetDir(remote_dir_);
}

void DiskClientGUI::RefreshData(disk::FileInfoList file_list, std::string cur_dir)
{
    remote_dir_ = cur_dir;
    file_list_ = file_list;
    QString view_dir = "";
    QString dir_str = QString::fromLocal8Bit(cur_dir.c_str());
    auto dir_list = dir_str.split("/");
    for (const auto& dir : dir_list)
    {
        auto d = dir.trimmed();
        if (d.isEmpty()) continue;
        view_dir += d;
        view_dir += " > ";
    }
    ui->dir_label->setText(view_dir);

    auto tab = ui->filetableWidget;
    while (tab->rowCount() > 0)
    {
        tab->removeRow(0);
    }

    for (const auto& file : file_list.files())
    {
        tab->insertRow(0);
        auto check = new QCheckBox(tab);
        auto layout = new QHBoxLayout();
        auto widget = new QWidget(tab);
        layout->addWidget(check);
        layout->setMargin(0);
        layout->setAlignment(check, Qt::AlignCenter);
        widget->setLayout(layout);
        tab->setCellWidget(0, 0, widget);

        string filename = file.filename();
        string iconpath = FILE_ICON_PATH;
        iconpath += GetIconFilename(filename, file.is_dir());
        iconpath += "Type.png";

        string file_type = GetFileSuffix(filename);
        if (file.is_dir())
        {
            file_type = "文件夹";
        }
        else
        {
            file_type += "文件";
        }
        
        QString qname = QString::fromLocal8Bit(filename.c_str());
        QString qfile_type = QString::fromLocal8Bit(file_type.c_str());
        //QString qname = filename.c_str();
        tab->setItem(0, 1, new QTableWidgetItem(QIcon(iconpath.c_str()), qname));
        tab->setItem(0, 2, new QTableWidgetItem(file.filetime().c_str()));
        tab->setItem(0, 3, new QTableWidgetItem(qfile_type));
        if (file.is_dir())
            tab->setItem(0, 4, new QTableWidgetItem("-"));
        else
            tab->setItem(0, 4, new QTableWidgetItem(GetSizeString(file.filesize()).c_str()));
    } 
}

static QPoint global_pos;
static bool is_new_dir = false;

void DiskClientGUI::NewDir()
{ 
    is_new_dir = true;
    auto tab = ui->filetableWidget;
    tab->insertRow(0);
    auto check = new QCheckBox(tab);
    auto layout = new QHBoxLayout();
    auto widget = new QWidget(tab);
    check->setChecked(true);
    layout->addWidget(check);
    layout->setMargin(0);
    layout->setAlignment(check, Qt::AlignCenter);
    widget->setLayout(layout);
    tab->setCellWidget(0, 0, widget);

    string filename = "新建文件夹";
    string iconpath = FILE_ICON_PATH;
    iconpath += GetIconFilename(filename, true);
    iconpath += "Type.png";

    QString qname = QString::fromLocal8Bit(filename.c_str());
    //QString qname = filename.c_str();  /// 服务器在linux跑开放  

    QTableWidgetItem* item = new QTableWidgetItem(QIcon(iconpath.c_str()), qname);
    item->setFlags(item->flags() | Qt::ItemIsEditable); // 确保项是可编辑的
    tab->setItem(0, 1, item);
    tab->editItem(tab->item(0, 1));
    tab->setItem(0, 2, new QTableWidgetItem(GetCurTime(time(0)).c_str()));
}

void DiskClientGUI::DirRename(QTableWidgetItem* item)
{
    if (!is_new_dir) return;
    if (item->row() == 0 && item->column() == 1)
    {
        string dir = item->text().toLocal8Bit();
        if (dir == "新建文件夹") return;
        ifm_->NewDir(remote_dir_ + "/" + dir);
    }
}

bool DiskClientGUI::eventFilter(QObject* object, QEvent* event)
{
    if (!is_new_dir) return QObject::eventFilter(object, event);
    if (object == ui->filetableWidget)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
            {
                // 处理回车键按下事件
                if (ui->filetableWidget->rowCount() == 0) return QObject::eventFilter(object, event);
                QString filename = ui->filetableWidget->item(0, 1)->text();
                triggerItemChanged(filename);
            }
        }
        else if (event->type() == QEvent::FocusOut)
        {
            // 处理焦点移开事件
            if (ui->filetableWidget->rowCount() == 0) return QObject::eventFilter(object, event);
            QString filename = ui->filetableWidget->item(0, 1)->text();
            triggerItemChanged(filename);
        }
    }
    return QObject::eventFilter(object, event);
}

void DiskClientGUI::triggerItemChanged(QString filename)
{
    if (!is_new_dir) return;
    QTableWidgetItem* item = ui->filetableWidget->item(0, 1);
    if (item)
    {
        item->setText(filename);       // 然后恢复原内容
    }
}

void DiskClientGUI::Checkall()
{
    auto tab = ui->filetableWidget;
    for (int i = 0; i < tab->rowCount(); i++)
    {
        auto w = tab->cellWidget(i, 0);
        if (!w) continue;
        auto check = (QCheckBox*)w->layout()->itemAt(0)->widget();
        if (!check) continue;
        check->setChecked(ui->checkallBox->isChecked());
    }
}

void DiskClientGUI::Back()
{
    if (remote_dir_.empty() || remote_dir_ == "/") return;

    std::string tmp = remote_dir_;
    if (tmp[tmp.size() - 1] == '/')
    {
        tmp = tmp.substr(0, tmp.size() - 1);
    }
    int index = tmp.find_last_of('/');
    remote_dir_ = tmp.substr(0, index);
    ifm_->GetDir(remote_dir_);
}

void DiskClientGUI::Root()
{
    ifm_->GetDir("");
}

void DiskClientGUI::DoubleClicked(int row, int column)
{
    auto item = ui->filetableWidget->item(row, 1);
    QString dir = item->text();
    std::string filename = dir.toLocal8Bit();
    for (const auto& file : file_list_.files())
    {
        if (filename == file.filename())
        {
            if (!file.is_dir()) return;
        }
        else
        {
            continue;
        }
    }
    std::string path = remote_dir_ + "/" + filename;
    ifm_->GetDir(path);
}

void DiskClientGUI::Delete()
{
    auto tab = ui->filetableWidget;
    int row_count = tab->rowCount();
    std::vector<int> rows;
    int count = 0;
    for (int i = 0; i < row_count; i++)
    {
        auto w = tab->cellWidget(i, 0);
        if (!w) continue;
        auto check = (QCheckBox*)w->layout()->itemAt(0)->widget();
        if (!check) continue;
        if (check->isChecked())
        {
            rows.push_back(i);
            count++;
        }
    }

    if (count == 0)
    {
        MyMessageBox::critical(this, QString::fromLocal8Bit("请选择删除的文件"), 
            QString::fromLocal8Bit("系统提示"), MyMessageBox::Close);
        return;
    }

    std::string tip_text = "确定要删除";
    string filename = "\"";
    if (count == 1)
    {
        filename += tab->item(rows[0], 1)->text().toLocal8Bit();
        tip_text += filename;
        tip_text += "\"";
    }
    else
    {
        tip_text += "这" + std::to_string(count) + "个";
    }

    tip_text += "文件吗";

    auto ret = MyMessageBox::information(this, QString::fromLocal8Bit(tip_text.c_str()),
        QString::fromLocal8Bit("系统提示"), MyMessageBox::Ok | MyMessageBox::Cancel);
    if (ret == MyMessageBox::Cancel) return;

    for (const auto& row : rows)
    {
        filename = tab->item(row, 1)->text().toLocal8Bit();
        disk::FileInfo file_info;
        file_info.set_filename(filename);
        file_info.set_filedir(remote_dir_);
        for (const auto& file : file_list_.files())
        {
            if (filename == file.filename())
            {
                file_info.set_is_dir(file.is_dir());
            }
        }
        ifm_->DeleteFile(file_info);
    }
}

static bool mouse_press = false;
static QPoint mouse_point;
void DiskClientGUI::mouseMoveEvent(QMouseEvent* ev)
{
    //没有按下，处理原事件
    if (!mouse_press)
    {
        QWidget::mouseMoveEvent(ev);
        return;
    }
    auto cur_pos = ev->globalPos();
    this->move(cur_pos - mouse_point);
}

void DiskClientGUI::mousePressEvent(QMouseEvent* ev)
{
    //鼠标左键按下记录位置
    if (ev->button() == Qt::LeftButton)
    {
        mouse_press = true;
        mouse_point = ev->pos();
    }

}

void DiskClientGUI::mouseReleaseEvent(QMouseEvent* ev)
{
    mouse_press = false;
}

void DiskClientGUI::contextMenuEvent(QContextMenuEvent* ev)
{
    // 将filetableWidget的位置转换为全局坐标系中的位置
    QPoint fileTableTopLeftGlobal = ui->filetableWidget->mapToGlobal(QPoint(0, 0));

    // 创建一个新的QRect，代表filetableWidget在全局坐标系中的几何位置
    QRect fileTableRectGlobal(fileTableTopLeftGlobal, ui->filetableWidget->size());

    // 事件的全局位置
    QPoint eventPosGlobal = ev->globalPos();

    /// 记录新建目录鼠标位置
    global_pos = ev->globalPos();

    // 检查事件位置是否在filetableWidget内（使用全局坐标）
    if (fileTableRectGlobal.contains(eventPosGlobal))
    {
        QMenu context;
        context.addAction(ui->action_new_dir);
        context.addAction(ui->upaction);
        context.addAction(ui->downaction);
        context.addAction(ui->refreshaction);
        context.exec(eventPosGlobal);
    }
    else
    {
        // 在filetableWidget之外的其他处理...
    }
}

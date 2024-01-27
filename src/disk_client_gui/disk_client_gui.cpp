#include "disk_client_gui.h"
#include "login_gui.h"
#include "ui_disk_client_gui.h"
#include "tools.h"

#include <QMouseEvent>
#include <QHBoxLayout>

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
    tab->setColumnWidth(1, 500);
    tab->setColumnWidth(2, 150);
    tab->setColumnWidth(3, 120);

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
    ifm_->GetDir("");
}

void DiskClientGUI::RefreshData(disk::FileInfoList file_list, std::string cur_dir)
{
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
        
        QString qname = QString::fromLocal8Bit(filename.c_str());
        tab->setItem(0, 1, new QTableWidgetItem(QIcon(iconpath.c_str()), qname));
        tab->setItem(0, 2, new QTableWidgetItem(file.filetime().c_str()));
        if (file.is_dir()) continue;
        tab->setItem(0, 3, new QTableWidgetItem(GetSizeString(file.filesize()).c_str()));
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

#ifndef DISK_CLIENT_GUI_H
#define DISK_CLIENT_GUI_H

#include <QWidget>

#include "ifile_manager.h"

namespace Ui {
    class DiskClientGUI;
}

class LoginGUI;

class DiskClientGUI  : public QWidget
{
    Q_OBJECT

public:
    explicit DiskClientGUI(iFileManager* f, QWidget *parent = 0);
    ~DiskClientGUI();

    void DiskClientGUI::mouseMoveEvent(QMouseEvent* ev);
    void DiskClientGUI::mousePressEvent(QMouseEvent* ev);
    void DiskClientGUI::mouseReleaseEvent(QMouseEvent* ev);

    void set_ifm(iFileManager* f) { this->ifm_ = f; }
public slots:
    /// @brief 接收登陆界面传递的用户名
    void SetUsername(std::string username);

    void Refresh();
    void RefreshData(disk::FileInfoList file_list, std::string cur_dir);

    void Checkall();
private:
    Ui::DiskClientGUI* ui;
    LoginGUI* login_gui_;
    iFileManager* ifm_ = nullptr;
};

#endif // DISK_CLIENT_GUI_H

#ifndef DISK_CLIENT_GUI_H
#define DISK_CLIENT_GUI_H

#include <QWidget>
#include <QMessageBox>
#include <QTableWidgetItem>

#include "ifile_manager.h"

namespace Ui {
    class DiskClientGUI;
}

class LoginGUI;

class DiskClientGUI  : public QWidget
{
    Q_OBJECT

public:
    explicit DiskClientGUI(LoginGUI * login_gui,iFileManager* f, QWidget *parent = 0);
    ~DiskClientGUI();

    void DiskClientGUI::mouseMoveEvent(QMouseEvent* ev);
    void DiskClientGUI::mousePressEvent(QMouseEvent* ev);
    void DiskClientGUI::mouseReleaseEvent(QMouseEvent* ev);

    void contextMenuEvent(QContextMenuEvent* ev) override;

    bool eventFilter(QObject* object, QEvent* event) override;

    void set_ifm(iFileManager* f) { this->ifm_ = f; }
private:
    void triggerItemChanged(QString filename);

    std::set<int> GetSelectRow();
public slots:
    void Refresh();
    void RefreshData(disk::FileInfoList file_list, std::string cur_dir);

    void NewDir();
    void DirRename(QTableWidgetItem* item);

    /// 回退目录
    void Back();
    void Root();
    void DoubleClicked(int row, int column);

    void Delete();

    void RefreshDiskInfo(disk::DiskInfo info);

    void Upload();

    void Download();

    void Checkall();

    void FileEnc();

    void ErrorSlot(std::string err);

    /// @brief 文件校验结果通知
    /// @param type 区分上传还是下载，上传为 1 下载为 2 
    /// @param is_success 是否校验成功
    void FileCheck(int type ,bool is_success);

    /// @brief root用户有添加用户权限
    void AddUser();

    void MyTab();
    void TaskTab();
private:
    Ui::DiskClientGUI* ui;
    LoginGUI* login_gui_;
    iFileManager* ifm_ = nullptr;
    std::string remote_dir_ = "";
    disk::FileInfoList file_list_;
};

#endif // DISK_CLIENT_GUI_H

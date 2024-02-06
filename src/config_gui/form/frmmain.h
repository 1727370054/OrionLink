#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QDialog>
#include <string>

namespace Ui {
class frmMain;
}
namespace google
{
    namespace protobuf
    {
        class Message;
    }
}

namespace msg
{
    class Config;
}

class frmMain : public QDialog
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

    /// 根据message和config生成界面
    void InitGUI();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
    std::string UTF8ToGBK(const char * data);

private slots:
    void initForm();
    void buttonClick();
    /// 刷新显示配置列表
    void Refresh();
    /// 显示日志在列表中
    void AddLog(const char* log);
    /// 保存配置
    void Save();
    /// 删除选择的配置
    void DelConfig();
    /// 编辑配置
    void EditConfig();
    /// 加载微服务配置项，从配置中心获取，并解析生成界面
    bool LoadConfig(const char* service_ip, int service_port);
    /// 选择proto文件，并加载，动态编译解析
    void LoadProto();
    /// 保存配置信息的响应
    void SaveMessgeCB(bool is_ok, const char* desc);
    /// 删除配置信息的响应
    void DelMessgeCB(bool is_ok, const char* desc);
private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();
signals:
    void SigSaveMessgeCB(bool is_ok, const char* desc);
    void SigDelMessgeCB(bool is_ok, const char* desc);

private:
    Ui::frmMain* ui;
    /// 记录基础配置信息的行数，同于区分哪些是proto文件生成的
    int config_row_count_ = 0;
    /// 用于存储动态解析proto文件的配置信息
    google::protobuf::Message* dynamic_msg_ = nullptr;
    /// 用于存储从配置中心获取的配置项
    msg::Config* config_ = nullptr;
};

#endif // UIDEMO01_H

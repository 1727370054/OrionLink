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

    /// ����message��config���ɽ���
    void InitGUI();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
    std::string UTF8ToGBK(const char * data);

private slots:
    void initForm();
    void buttonClick();
    /// ˢ����ʾ�����б�
    void Refresh();
    /// ��ʾ��־���б���
    void AddLog(const char* log);
    /// ��������
    void Save();
    /// ɾ��ѡ�������
    void DelConfig();
    /// �༭����
    void EditConfig();
    /// ����΢������������������Ļ�ȡ�����������ɽ���
    bool LoadConfig(const char* service_ip, int service_port);
    /// ѡ��proto�ļ��������أ���̬�������
    void LoadProto();
    /// ����������Ϣ����Ӧ
    void SaveMessgeCB(bool is_ok, const char* desc);
    /// ɾ��������Ϣ����Ӧ
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
    /// ��¼����������Ϣ��������ͬ��������Щ��proto�ļ����ɵ�
    int config_row_count_ = 0;
    /// ���ڴ洢��̬����proto�ļ���������Ϣ
    google::protobuf::Message* dynamic_msg_ = nullptr;
    /// ���ڴ洢���������Ļ�ȡ��������
    msg::Config* config_ = nullptr;
};

#endif // UIDEMO01_H

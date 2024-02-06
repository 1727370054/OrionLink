#include "auth_client.h"
#include "disk_client_gui.h"
#include "login_gui.h"
#include "file_manager.h"
#include "ifile_manager.h"
#include "tools.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>

using namespace std;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile file(":/res/qss/style-2.qss");/*QSS文件所在的路径*/

    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    app.setStyleSheet(stylesheet);
    file.close();

    QApplication::setWindowIcon(QIcon(":/XMSDiskClientGui/disk_logo.ico"));

    std::string gateway_ip = GetHostByName(OL_GATEWAY_SERVER_NAME);
    //std::string gateway_ip = "192.168.1.7";
    AuthClient::GetInstance()->set_server_ip(gateway_ip.c_str());
    AuthClient::GetInstance()->set_server_port(API_GATEWAY_PORT);
    AuthClient::GetInstance()->set_auto_connect(true);
    AuthClient::GetInstance()->StartConnect();

    LoginGUI login_gui;
    if (login_gui.exec() == QDialog::Rejected)
    {
        return -1;
    }

    FileManager fm;
    fm.InitFileManager(gateway_ip, API_GATEWAY_PORT);
    fm.set_login_info(AuthClient::GetInstance()->GetCurLogin());
    DiskClientGUI w(&login_gui,&fm);
    w.show();

    return app.exec();
}

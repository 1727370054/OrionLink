#include "auth_client.h"
#include "disk_client_gui.h"
#include "file_manager.h"
#include "tools.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile file(":/res/qss/style-2.qss");/*QSS文件所在的路径*/

    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    app.setStyleSheet(stylesheet);
    file.close();

    AuthClient::RegisterMsgCallback();
    std::string gateway_ip = GetHostByName("ol_gateway_server");
    AuthClient::GetInstance()->set_server_ip(gateway_ip.c_str());
    AuthClient::GetInstance()->set_server_port(API_GATEWAY_PORT);
    AuthClient::GetInstance()->set_auto_connect(true);
    AuthClient::GetInstance()->StartConnect();
    
    FileManager fm;
    DiskClientGUI w(&fm);
    w.show();

    return app.exec();
}

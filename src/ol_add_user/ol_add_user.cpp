#include <iostream>
#include <string>
#include "auth_client.h"
#include <thread>
using namespace std;
int main(int argc, char *argv[])
{
    string username = "";
    string rolename = "";
    string password = "";
    cout << "Username:";
    cin >> username;
    cout << "Rolename:";
    cin >> rolename;
    cout << "Password:";
    cin >> password;
    cout << username << "/" << password << endl;
    AuthClient::RegisterMsgCallback();
    AuthClient::GetInstance()->set_server_ip("127.0.0.1");
    AuthClient::GetInstance()->set_server_port(AUTH_PORT);
    AuthClient::GetInstance()->StartConnect();
    while (!AuthClient::GetInstance()->is_connected())
    {
        this_thread::sleep_for(100ms);
    }
    msg::AddUserReq adduser;
    adduser.set_username(username);
    adduser.set_password(password);
    adduser.set_rolename(rolename);
    AuthClient::GetInstance()->AddUserReq(&adduser);
    this_thread::sleep_for(500ms);
    return 0;
}

#include "auth_client.h"
#include "tools.h"
#include "msg_comm.pb.h"

using namespace msg;

void AuthClient::LoginReq(std::string username, std::string password)
{
    msg::LoginReq request;
    request.set_username(username);
    auto md5_passwd = OLMD5_base64((unsigned char*)password.c_str(), password.size());
    request.set_password(md5_passwd);
    std::cout << request.DebugString() << std::endl;
    SendMsg(MSG_LOGIN_REQ, &request);
}

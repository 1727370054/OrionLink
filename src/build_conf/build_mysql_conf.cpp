#include <iostream>
#include <fstream>
#include <cstring>
#include <termio.h>

using namespace std;

#define MYSQL_CONFIG_PATH "/etc/ol_mysql_init.conf"

struct MySQLInfo
{
    char host[128] = {0};
    char user[128] = {0};
    char pass[128] = {0};
    char db_name[128] = {0};
    int port = 3306;
};

char _getch()
{
    termios new_tm;
    /// 原来的模式
    termios old_tm;
    int fd = 0;
    if (tcgetattr(fd, &old_tm) < 0)
        return -1;
    /// 更改为原始模式，没有回显
    cfmakeraw(&new_tm);
    if (tcsetattr(fd, TCSANOW, &new_tm) < 0)
    {
        return -1;
    }
    char c = getchar();
    if (tcsetattr(fd, TCSANOW, &old_tm) < 0)
    {
        return -1;
    }

    return c;
}

std::string InputPassword()
{
    /// 清空缓冲
    cin.ignore(4096, '\n');
    string password = "";
    for (;;)
    {
        char a = _getch(); /// 获取输入字符不显示
        if (a <= 0 || a == '\n' || a == '\r') break;
        password += a;
        cout << "*" << flush;
    }

    return password;
}

int main(int argc, char *argv[])
{
    MySQLInfo info;
    cout << "======= input the db set =======" << endl;
    cout << "input db host:";
    cin >> info.host;
    cout << "input db user:";
    cin >> info.user;
    cout << "input db pass:";
    std::string password = InputPassword();
	strncpy(info.pass, password.c_str(), sizeof(info.pass) - 1);
	info.pass[sizeof(info.pass) - 1] = '\0';
    cout << endl;
    cout << "input db dbname(orion_link):";
    cin >> info.db_name;
    cout << "input db port(3306):";
    cin >> info.port;

    ofstream ofs;
    ofs.open(MYSQL_CONFIG_PATH, ios::binary);
    if (ofs.is_open())
    {
        ofs.write((char *)&info, sizeof(info));
        ofs.close();
        cout << "write config file success!" << endl;
    }
    else
    {
        cout << "write config file failed!" << endl;
    }

    return 0;
}

#include <iostream>
#include <fstream>

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

int main(int argc, char *argv[])
{
    MySQLInfo info;
    cout << "input the db set" << endl;
    cout << "input db host:";
    cin >> info.host;
    cout << "input db user:";
    cin >> info.user;
    cout << "input db pass:";
    cin >> info.pass;
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

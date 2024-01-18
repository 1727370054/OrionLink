#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    // 3 �����˳�����೤ʱ������
    int timeval = 3;
    if (argc < 3)
    {
        cout << "Useage: ./watchdog 3 ./register_server 20011" << endl;
        return -1;
    }
    // �����ӽ��̣��������˳�������1���̣��ػ����̺�̨ ��
    int pid = 0;
    pid = fork();
    if (pid > 0)
        exit(0); // �������˳� ����1����
    setsid();    // �����µĻỰ �븸��������
    umask(0);    // ����

    // �����ػ�����

    // �������
    timeval = atoi(argv[1]);

    // ��������
    string cmd = "";
    for (int i = 2; i < argc; i++)
    {
        cmd += " ";
        cmd += argv[i];
    }
    cout << cmd << endl;
    for (;;)
    {
        // �������̣����ȴ������˳�
        int ret = system(cmd.c_str());
        sleep(timeval);
    }

    return 0;
}
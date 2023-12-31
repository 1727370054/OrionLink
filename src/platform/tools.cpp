#include "tools.h"

#include <cstdio>

#ifdef _WIN32
#include <io.h>
#else
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#endif // _WIN32


std::string GetDirData(std::string path)
{
    std::string data;
#ifdef _WIN32
    /// file һ���ṹ�壬���ڴ洢�ҵ���ÿ���ļ�����Ϣ�������ơ���С�����Եȣ�
    _finddata_t file;
    /// "paath + /*.*"����ʾ���������ļ���
    std::string dir_path = path + "/*.*";
    /// dir �洢�����������Ļ���
    intptr_t dir = _findfirst(dir_path.c_str(), &file);
    if (dir < 0) return data;

    do
    {
        if (file.attrib & _A_SUBDIR) continue;
        char buf[1024] = {0};
        sprintf_s(buf, "%s,%u;", file.name, file.size);
        data += buf;

    } while (_findnext(dir, &file) == 0);
#else
	const char* dir = path.c_str();
	DIR* dp = NULL;
	struct dirent* entry = NULL;
	struct stat statbuf;

	if (dir == NULL)
		return data;

	dp = opendir(dir);
	if (dp == NULL)
	{
		/// �޷���Ŀ¼������Ŀ¼�����ڻ���Ȩ������
		return data;
	}

	char buf[1024] = { 0 };
	while ((entry = readdir(dp)) != NULL) {
		std::string fullPath = path + "/" + entry->d_name;
		if (lstat(fullPath.c_str(), &statbuf) == -1)
		{
			continue;
		}
		if (S_ISDIR(statbuf.st_mode))
		{
			continue; /// ����Ŀ¼
		}
		snprintf(buf, sizeof(buf), "%s,%ld;", entry->d_name, statbuf.st_size);
		data += buf;
	}

	closedir(dp); /// �ر�Ŀ¼ָ��
#endif // _WIN32

    /// ȥ����β�ֺ�
    if (!data.empty())
    {
        data = data.substr(0, data.size() - 1);
    }

    return data;
}

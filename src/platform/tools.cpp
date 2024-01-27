#include "tools.h"

#include <cstdio>
#include <string>
#include <openssl/md5.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/sha.h>

#ifdef _WIN32
#include <io.h>
#include <windows.h>
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
    /// file 一个结构体，用于存储找到的每个文件的信息（如名称、大小、属性等）
    _finddata_t file;
    /// "path + /*.*"（表示查找所有文件）
    std::string dir_path = path + "/*.*";
    /// dir 存储搜索的上下文或句柄
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
		/// 无法打开目录，可能目录不存在或者权限问题
		return data;
	}

	char buf[1024] = { 0 };
	while ((entry = readdir(dp)) != NULL) 
	{
		std::string fullPath = path + "/" + entry->d_name;
		if (lstat(fullPath.c_str(), &statbuf) == -1)
		{
			continue;
		}
		if (S_ISDIR(statbuf.st_mode))
		{
			continue; /// 跳过目录
		}
		snprintf(buf, sizeof(buf), "%s,%ld;", entry->d_name, statbuf.st_size);
		data += buf;
	}

	closedir(dp); /// 关闭目录指针
#endif // _WIN32

    /// 去掉结尾分号
    if (!data.empty())
    {
        data = data.substr(0, data.size() - 1);
    }

    return data;
}

XCOM_API std::list<ToolFileInfo> GetDirList(std::string path)
{
	std::list<ToolFileInfo> file_list;
#ifdef _WIN32
	/// file 一个结构体，用于存储找到的每个文件的信息（如名称、大小、属性等）
	_finddata_t file;
	/// "path + /*.*"（表示查找所有文件）
	std::string dir_path = path + "/*.*";
	/// dir 存储搜索的上下文或句柄
	intptr_t dir = _findfirst(dir_path.c_str(), &file);
	if (dir < 0) return file_list;

	do
	{
		ToolFileInfo file_info;
		if (file.attrib & _A_SUBDIR)
		{
			file_info.is_dir = true;
		}
		file_info.filename = file.name;
		file_info.filesize = file.size;
		file_info.time_write = file.time_write;
		file_info.time_str = GetCurTime(file.time_write);
		file_list.push_back(file_info);

	} while (_findnext(dir, &file) == 0);
#else
	const char* dir = path.c_str();
	DIR* dp = NULL;
	struct dirent* entry = NULL;
	struct stat statbuf;

	if (dir == NULL)
		return file_list;

	dp = opendir(dir);
	if (dp == NULL)
	{
		/// 无法打开目录，可能目录不存在或者权限问题
		return file_list;
	}

	while ((entry = readdir(dp)) != NULL) 
	{
		ToolFileInfo file_info;
		std::string fullPath = path + "/" + entry->d_name;
		if (lstat(fullPath.c_str(), &statbuf) == -1)
		{
			continue;
		}
		if (S_ISDIR(statbuf.st_mode))
		{
			file_info.is_dir = true;
		}
		file_info.filename = entry->d_name;
		file_info.filesize = statbuf.st_size;
		file_info.time_write = statbuf.st_mtime;
		file_info.time_str = GetCurTime(statbuf.st_mtime);
		file_list.push_back(file_info);
	}

	closedir(dp); /// 关闭目录指针
#endif // _WIN32

	return file_list;
}

std::string GetIconFilename(std::string filename, bool is_dir)
{
	std::string iconpath = "Other";
	std::string filetype = "";
	int pos = filename.find_last_of(".");
	if (pos > 0)
	{
		filetype = filename.substr(pos + 1);
	}

	/// 转换为小写 ，第三个参数是输出
	transform(filetype.begin(), filetype.end(), filetype.begin(), ::tolower);

	if (is_dir)
	{
		iconpath = "Folder";
	}
	else if (filetype == "jpg" || filetype == "png" || filetype == "gif")
	{
		iconpath = "Img";
	}
	else if (filetype == "doc" || filetype == "docx" || filetype == "wps")
	{
		iconpath = "Doc";
	}
	else if (filetype == "rar" || filetype == "zip" || filetype == "7z" || filetype == "gzip")
	{
		iconpath = "Rar";
	}
	else if (filetype == "ppt" || filetype == "pptx")
	{
		iconpath = "Ppt";
	}
	else if (filetype == "xls" || filetype == "xlsx")
	{
		iconpath = "Xls";
	}
	else if (filetype == "pdf")
	{
		iconpath = "Pdf";
	}
	else if (filetype == "doc" || filetype == "docx" || filetype == "wps")
	{
		iconpath = "Doc";
	}
	else if (filetype == "avi" || filetype == "mp4" || filetype == "mov" || filetype == "wmv")
	{
		iconpath = "Video";
	}
	else if (filetype == "mp3" || filetype == "pcm" || filetype == "wav" || filetype == "wma")
	{
		iconpath = "Music";
	}
	else
	{
		iconpath = "Other";
	}
	return iconpath;
}

XCOM_API std::string GetSizeString(long long size)
{
	std::string filesize_str = "";
	if (size > 1024 * 1024 * 1024) /// GB
	{
		double gb_size = (double)size / (double)1024 * 1024 * 1024;
		long long tmp = gb_size * 100;
		std::stringstream ss;
		ss << tmp / 100;
		if (tmp % 100 > 0)
		{
			ss << "." << tmp % 100;
		}
		ss << "GB";
		filesize_str = ss.str();
	}
	else if (size > 1024 * 1024) //MB
	{
		double ms_size = (double)size / (double)(1024 * 1024);
		long long tmp = ms_size * 100;

		std::stringstream ss;
		ss << tmp / 100;
		if (tmp % 100 > 0)
			ss << "." << tmp % 100;
		ss << "MB";
		filesize_str = ss.str();
	}
	else if (size > 1024) //KB
	{
		float kb_size = (float)size / (float)(1024);
		long long tmp = kb_size * 100;
		std::stringstream ss;
		ss << tmp / 100;
		if (tmp % 100 > 0)
			ss << "." << tmp % 100;
		ss << "KB";
		filesize_str = ss.str();
	}
	else //B
	{
		float b_size = size / (float)(1024);
		long long tmp = b_size * 100;

		std::stringstream ss;
		ss << size;
		ss << "B";
		filesize_str = ss.str();
	}
	return filesize_str;
}

int Base64Encode(const unsigned char* in, int len, char* out_base64)
{
	if (!in || len <= 0 || !out_base64) return 0;

	// 创建一个内存BIO（BIO_s_mem），用于保存源数据
	BIO* mem_bio = BIO_new(BIO_s_mem());
	if (!mem_bio) return 0;

	/// base64的过滤器
	BIO* b64_bio = BIO_new(BIO_f_base64());
	if (!b64_bio)
	{
		BIO_free(mem_bio);
		return 0;
	}

	/// 64字节不加换行符'\n'
	BIO_set_flags(b64_bio, BIO_FLAGS_BASE64_NO_NL);

	/// 形成BIO链
	/// b64-mem
	BIO_push(b64_bio, mem_bio);

	/// 往链表头部写入，base64过滤器处理后转入下一个节点
	/// 对链表写入会调用编码
	/// 返回写入数据的大小
	int ret = BIO_write(b64_bio, in, len);
	if (ret <= 0)
	{
		/// 清理整个链表
		BIO_free_all(b64_bio);
		return 0;
	}
	/// 刷新缓存，写入链表的mem
	BIO_flush(b64_bio);

	/// 从链表源mem内存读取
	BUF_MEM* p_data  = nullptr;
	BIO_get_mem_ptr(b64_bio, &p_data);
	int out_size = 0;
	if (p_data)
	{
		memcpy(out_base64, p_data->data, p_data->length);
		out_size = p_data->length;
	}

	BIO_free_all(b64_bio);
	return out_size;
}

int Base64Decode(const char* in, int len, unsigned char* out_data)
{
	if (!in || len <= 0 || !out_data) return 0;

	/// 内存源(密文)
	BIO* mem_bio = BIO_new_mem_buf(in, len);
	if (!mem_bio) return 0;

	BIO* b64_bio = BIO_new(BIO_f_base64());
	if (!b64_bio)
	{
		BIO_free(mem_bio);
		return 0;
	}
	/// 64字节不加换行符'\n'
	BIO_set_flags(b64_bio, BIO_FLAGS_BASE64_NO_NL);

	BIO_push(b64_bio, mem_bio);

	/// 读取解码后的数据
	size_t size;
	BIO_read_ex(b64_bio, out_data, len, &size);
	BIO_free_all(b64_bio);

	return size;
}

std::string GetCurTime(int timestamp, std::string format)
{
	char buf[128] = { 0 };
	time_t tm = timestamp;
	if (tm <= 0)
		tm = time(0);
	strftime(buf, sizeof(buf), format.c_str(), localtime(&tm));
	return buf;
}

/// 生成md5 128bit(16字节) 
unsigned char* OLMD5(const unsigned char* d, unsigned long n, unsigned char* md)
{
	return MD5(d, n, md);
}

/// @brief 生成md5 128bit(16字节) 再经过base64转化为字符串
std::string OLMD5_base64(const unsigned char* d, unsigned long n)
{
	unsigned char buf[16] = { 0 };
	char base64[25] = { 0 };
	OLMD5(d, n, buf);
	Base64Encode(buf, 16, base64);
	base64[24] = '\0';
	return base64;
}

std::string GetHostByName(std::string host_name)
{
#ifdef _WIN32
	static bool is_init = false;
	if (!is_init)
	{
		WORD sock_version = MAKEWORD(2, 2);
		WSADATA wsa;
		if (WSAStartup(sock_version, &wsa) != 0)
		{
			return "";
		}
		is_init = true;
	}
#endif // _WIN32
	auto host = gethostbyname(host_name.c_str());
	if (!host) return "";
	auto addr = host->h_addr_list;
	if (!addr) return "";

	/// 只取第一个
	return inet_ntoa(*(in_addr*)*addr);
}


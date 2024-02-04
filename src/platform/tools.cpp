#include "tools.h"

#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <random>
#include <openssl/md5.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/sha.h>

#ifdef _WIN32
#include <io.h>
#include <windows.h>
#include <direct.h>
#else
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/vfs.h>
#define _access access
#define _mkdir(d) mkdir(d,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
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
	std::string filetype = GetFileSuffix(filename);

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

std::string GetFileSuffix(std::string filename)
{
	std::string filetype = "";
	int pos = filename.find_last_of(".");
	if (pos > 0)
	{
		filetype = filename.substr(pos + 1);
	}

	/// 转换为小写 ，第三个参数是输出
	transform(filetype.begin(), filetype.end(), filetype.begin(), ::tolower);

	return filetype;
}

XCOM_API std::string GetSizeString(long long size)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2);

	if (size > 1024LL * 1024LL * 1024LL) // GB
	{ 
		ss << static_cast<double>(size) / (1024LL * 1024LL * 1024LL) << "GB";
	}
	else if (size > 1024LL * 1024LL) // MB
	{ 
		ss << static_cast<double>(size) / (1024LL * 1024LL) << "MB";
	}
	else if (size > 1024LL) // KB
	{ 
		ss << static_cast<double>(size) / 1024LL << "KB";
	}
	else // B
	{ 
		ss << size << "B";
	}
	return ss.str();
}

std::string FormatDir(const std::string& dir)
{
	std::string ret = "";
	bool is_sep = false; // 是否是/ 或者是 "\"
	for (int i = 0; i < dir.size(); i++)
	{
		if (dir[i] == '/' || dir[i] == '\\')
		{
			if (is_sep)
			{
				continue;
			}
			ret += '/';
			is_sep = true;
			continue;
		}
		ret += dir[i];
		is_sep = false;
	}
	return ret;
}

void StringSplit(std::vector<std::string>& vec, std::string str, std::string find)
{
	int pos1 = 0;
	int pos2 = 0;
	vec.clear();
	while ((pos2 = str.find(find, pos1)) != std::string::npos)
	{
		vec.push_back(str.substr(pos1, pos2 - pos1));
		pos1 = pos2 + find.size();
	}
	std::string tmp = str.substr(pos1);
	if ((int)tmp.size() > 0)
	{
		vec.push_back(tmp);
	}
}

void NewDir(std::string path)
{
	std::string tmp = FormatDir(path);
	std::vector<std::string> paths;
	StringSplit(paths, tmp, "/");

	std::string filename = "";
	for (const auto& s : paths)
	{
		filename += s + '/';
		if (_access(filename.c_str(), 0) == -1)
		{
			_mkdir(filename.c_str());
		}
	}
}

void DelFile(std::string path, bool is_dir)
{
#ifdef _WIN32
	if (is_dir)
	{
		DeleteDirectoryAndFiles(path);
	}
	else
	{
		DeleteFileA(path.c_str());
	}
#else
	if (is_dir)
	{
		DeleteDirectoryAndFiles(path);
	}
	else
	{
		remove(path.c_str());
	}
#endif // _WIN32
}

void DeleteDirectoryAndFiles(const std::string& path)
{
#ifdef _WIN32
	_finddata_t file;
	std::string dir_path = path + "/*.*";  // 寻找目录下所有文件
	intptr_t dir = _findfirst(dir_path.c_str(), &file);

	if (dir < 0) return;  // 如果没有找到文件或目录，返回

	do {
		if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0) continue;

		std::string filePath = path + "/" + file.name;
		if (file.attrib & _A_SUBDIR)
		{
			// 如果是子目录，则递归调用
			DeleteDirectoryAndFiles(filePath);
		}
		else 
		{
			// 如果不是子目录，尝试删除文件
			if (remove(filePath.c_str()) != 0)
			{
				_findclose(dir);
				return;
			}
		}
	} while (_findnext(dir, &file) == 0);

	_findclose(dir);  // 关闭句柄

	// 删除空目录
	if (_rmdir(path.c_str()) != 0) return;
#else
	DIR* dir = opendir(path.c_str());
	if (dir == nullptr)
		return;

	struct dirent* file;
	while ((file = readdir(dir)) != nullptr)
	{
		if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0)
			continue;

		std::string filePath = path + "/" + file->d_name;
		if (file->d_type == DT_DIR)
			DeleteDirectoryAndFiles(filePath);
		else
			remove(filePath.c_str());
	}

	closedir(dir);

	// 删除空目录
	rmdir(path.c_str());
#endif // _WIN32
}

long long GetDirSize(const char* path)
{
	if (!path) return 0;
	long long dir_size = 0;
	std::string dir_new = path;
#ifdef _WIN32
	_finddata_t file;
	dir_new += "/*.*";
	intptr_t dir = _findfirst(dir_new.c_str(), &file);
	if (dir < 0) return dir_size;

	do {
		if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0) continue;

		if (file.attrib & _A_SUBDIR)
		{
			dir_new = path;
			dir_new += "/";
			dir_new += file.name;
			dir_size += GetDirSize(dir_new.c_str());
		}
		else
		{
			dir_size += file.size;
		}
	} while (_findnext(dir, &file) == 0);
	_findclose(dir);  // 关闭句柄
#else
	DIR* dir = opendir(dir_new.c_str());
	if (dir == nullptr) return 0;

	struct dirent* file;
	struct stat statbuf;

	while ((file = readdir(dir)) != nullptr)
	{
		if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0)
			continue;
		std::string filePath = path + "/" + file->d_name;
		lstat(filePath.c_str(), &statbuf);
		if (file->d_type == DT_DIR)
			dir_size += GetDirSize(filePath.c_str());
		else
			dir_size += statbuf.st_size;
	}
	closedir(dir);
#endif // _WIN32

	return dir_size;
}

bool GetDiskSize(const char* path, unsigned long long* avail, unsigned long long* total, unsigned long long* free)
{
#ifdef _WIN32
	return GetDiskFreeSpaceExA(path, (ULARGE_INTEGER*)avail, (ULARGE_INTEGER*)total, (ULARGE_INTEGER*)free);
#else
	struct statfs disk_info;
	if (statfs(path, &disk_info) == -1) return false;

	*total = disk_info.f_blocks * disk_info.f_bsize;
	*free = disk_info.f_bfree * disk_info.f_bsize;
	*avail = disk_info.f_bavail * disk_info.f_bsize;
	
	return true;
#endif // _WIN32
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

bool SendEmail(const std::string& smtpServer, int port, const std::string& from, 
	const std::string& to, const std::string& subject, const std::string& message, 
	const std::string& username, const std::string& password)
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

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		std::cerr << "Socket creation failed" << std::endl;
		return false;
	}

	struct sockaddr_in remote;
	remote.sin_family = AF_INET;
	remote.sin_port = htons(port);
	remote.sin_addr.s_addr = inet_addr(GetHostByName(smtpServer.c_str()).c_str());

	if (connect(sock, (struct sockaddr*)&remote, sizeof(remote)) < 0) {
		std::cerr << "Connection to SMTP server failed." << std::endl;
		return false;
	}

	char buf[1024] = { 0 };
	recv(sock, buf, sizeof(buf), 0);
	std::cout << buf << std::endl;

	std::string send_msg = "HELO MSG\r\n";
	send(sock, send_msg.c_str(), send_msg.size(), 0);

	memset(buf, 0, sizeof(buf));
	recv(sock, buf, sizeof(buf), 0);
	std::cout << buf << std::endl;

	send_msg = "AUTH LOGIN\r\n";
	send(sock, send_msg.c_str(), send_msg.size(), 0);

	memset(buf, 0, sizeof(buf));
	recv(sock, buf, sizeof(buf), 0);
	std::cout << buf << std::endl;

	char username_base64[25] = { 0 };
	Base64Encode((unsigned char*)username.c_str(), username.size(), username_base64);
	std::string username_str = std::string(username_base64) + "\r\n";
	send(sock, username_str.c_str(), username_str.size(), 0);

	char password_base64[25] = { 0 };
	Base64Encode((unsigned char*)password.c_str(), password.size(), password_base64);
	std::string password_str = std::string(password_base64) + "\r\n";
	send(sock, password_str.c_str(), password_str.size(), 0);

	memset(buf, 0, sizeof(buf));
	recv(sock, buf, sizeof(buf), 0);
	std::cout << buf << std::endl;

	send_msg = "MAIL FROM:<" + from + ">\r\n";
	send(sock, send_msg.c_str(), send_msg.size(), 0);

	memset(buf, 0, sizeof(buf));
	recv(sock, buf, sizeof(buf), 0);
	std::cout << buf << std::endl;

	send_msg = "RCPT TO:<" + to + ">\r\n";
	send(sock, send_msg.c_str(), send_msg.size(), 0);

	memset(buf, 0, sizeof(buf));
	recv(sock, buf, sizeof(buf), 0);
	std::cout << buf << std::endl;

	send_msg = "DATA\r\n";
	send(sock, send_msg.c_str(), send_msg.size(), 0);

	memset(buf, 0, sizeof(buf));
	recv(sock, buf, sizeof(buf), 0);
	std::cout << buf << std::endl;

	send_msg = "Subject: " + subject + "\r\n\r\n" + message + "\r\n.\r\n";
	send(sock, send_msg.c_str(), send_msg.size(), 0);

	memset(buf, 0, sizeof(buf));
	recv(sock, buf, sizeof(buf), 0);
	std::cout << buf << std::endl;

	std::string quitCmd = "QUIT\r\n";
	send(sock, quitCmd.c_str(), quitCmd.length(), 0);
	memset(buf, 0, sizeof(buf));
	recv(sock, buf, sizeof(buf), 0);
	std::cout << "QUIT response: " << buf << std::endl;

#ifdef _WIN32
	closesocket(sock);
#else
	close(sock);
#endif // _WIN32

	return true;
}

std::string GenerateNumericCode(int length)
{
	const char digits[] = "0123456789";
	std::string code;
	std::random_device rd;  // 用于获得一个随机数种子
	std::mt19937 gen(rd()); // 标准m​​ersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distrib(0, 9);

	for (int i = 0; i < length; ++i) 
	{
		code += digits[distrib(gen)]; // 从digits中随机选取一个字符
	}

	return code;
}

class CXAES :public OLAES
{
	///////////////////////////////////////////////////////////////////////////
	/// @brief 秘钥长度 128位（16字节） 192位 （24字节） 256位 (32字节)
	/// 长度不能超过32字节，返回失败
	/// 秘钥不足自动补充
	/// @param key 秘钥
	/// @param key_size 秘钥长度 字节 <=32 会自动补秘钥
	/// @param is_enc true 加密 false 解密
	/// @return 设置成功失败
	virtual bool SetKey(const char* key, int key_size, bool is_enc) override
	{
		if (key_size > 32 || key_size <= 0)
		{
			std::cerr << "AES key size error(>32 && <=0 )! key_size= " << key_size << std::endl;
			return false;
		}
		unsigned char aes_key[32] = { 0 };
		memcpy(aes_key, key, key_size);
		int bit_size = 0;
		if (key_size > 24)
		{
			bit_size = 32 * 8;
		}
		else if (key_size > 16)
		{
			bit_size = 24 * 8;
		}
		else
		{
			bit_size = 16 * 8;
		}

		/*
			if (bits != 128 && bits != 192 && bits != 256)
			 return -2;
		*/
		if (is_enc)
		{
			is_set_encode_ = true;
			if (AES_set_encrypt_key(aes_key, bit_size, &aes_) < 0)
			{
				return false;
			}
			return true;
		}
		is_set_decode_ = true;
		if (AES_set_decrypt_key(aes_key, bit_size, &aes_) < 0)
		{
			return false;
		}
		return true;
	}

	virtual void Drop() override
	{
		delete this;
	}

	///////////////////////////////////////////////////////////////////////////
	/// @brief 加密
	/// @param in 输入数据
	/// @param in_size 输入数据大小
	/// @param out 输出 数据空间要保证16字节的倍数
	/// @return  输出大小，失败返回<=0
	virtual long long Encrypt(const unsigned char* in, long long in_size, unsigned char* out) override
	{
		if (!in || in_size <= 0 || !out)
		{
			std::cerr << "Encrypt input data error" << std::endl;
			return 0;
		}

		if (!is_set_encode_)
		{
			std::cerr << "Encrypt password not set" << std::endl;
			return 0;
		}
		long long enc_byte = 0;
		//AES_encrypt 默认 AES_ecb_encrypt 可分块并行加密  cbc加密强度更大，每段时间与上一段相关
		/*
		每次加密一个数据块16个字节，不全的需要补充
			s0 = GETU32(in     ) ^ rk[0];
			s1 = GETU32(in +  4) ^ rk[1];
			s2 = GETU32(in +  8) ^ rk[2];
			s3 = GETU32(in + 12) ^ rk[3];
		*/
		unsigned char* p_in = 0;
		unsigned char* p_out = 0;
		unsigned char data[16] = { 0 };
		for (int i = 0; i < in_size; i += 16)
		{
			p_in = (unsigned char*)in + i;
			p_out = out + i;
			//处理不足16字节的补全
			if (in_size - i < 16)
			{
				memcpy(data, p_in, in_size - i);
				p_in = data;
			}
			enc_byte += 16;
			AES_encrypt(p_in, p_out, &aes_);
		}
		return enc_byte;
	}

	///////////////////////////////////////////////////////////////////////////
	/// @brief 解密
	/// @param in 输入数据
	/// @param in_size 输入数据大小
	/// @param out 输出 数据空间要保证16字节的倍数
	/// @return  输出大小，失败返回<=0
	virtual long long Decrypt(const unsigned char* in, long long in_size, unsigned char* out) override
	{

		if (!in || in_size <= 0 || !out || in_size % 16 != 0)
		{
			std::cerr << "Decrypt input data error" << std::endl;
			return 0;
		}

		if (!is_set_decode_)
		{
			std::cerr << "Decrypt password not set" << std::endl;
			return 0;
		}

		long long enc_byte = 0;
		//AES_encrypt 默认 AES_ecb_encrypt 可分块并行加密  cbc加密强度更大，每段时间与上一段相关
		/*
		每次加密一个数据块16个字节，不全的需要补充
			s0 = GETU32(in     ) ^ rk[0];
			s1 = GETU32(in +  4) ^ rk[1];
			s2 = GETU32(in +  8) ^ rk[2];
			s3 = GETU32(in + 12) ^ rk[3];
		*/
		unsigned char* p_in = 0;
		unsigned char* p_out = 0;
		unsigned char data[16] = { 0 };
		for (int i = 0; i < in_size; i += 16)
		{
			p_in = (unsigned char*)in + i;
			p_out = out + i;
			enc_byte += 16;
			AES_decrypt(p_in, p_out, &aes_);
		}
		return enc_byte;
	}
private:
	AES_KEY aes_;
	bool is_set_decode_ = false;
	bool is_set_encode_ = false;
};

OLAES* OLAES::Create()
{
	return new CXAES();
}

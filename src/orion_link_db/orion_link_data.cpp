#include "orion_link_data.h"

#include <cstring>
#include <fstream>
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <iconv.h>
#endif

using namespace std;

namespace ol
{
    OLData::OLData(const int* d)
    {
        this->type = OL_TYPE_LONG;
        if (!d) return;
        this->data = (char*)d;
        this->size = sizeof(int);
    }

    OLData::OLData(const char* data)
    {
        this->type = OL_TYPE_STRING;
        if (!data) return;
        this->data = data;
        this->size = (int)strlen(data);
    }

    bool OLData::LoadFile(const char* filename)
    {
        if (!filename) return false;

        fstream in(filename, ios::in | ios::binary);
        if (!in.is_open())
        {
            cerr << "open " << filename << " failed!" << endl;
            return false;
        }

        in.seekg(0, ios::end);
        this->size = (int)in.tellg();
        in.seekg(0, ios::beg);
        if (this->size <= 0)
        {
            cerr << filename << " is empty!" << endl;
            return false;
        }

        this->data = new char[this->size];
        int readed = 0;
        while (readed < this->size)
        {
            in.read((char*)this->data + readed, this->size - readed);
            int cur_len = in.gcount();
            if (cur_len == 0)
            {
                if (in.eof())
                    break;
                else
                {
                    Drop();
                    in.close();
                    return false;
                }
            }
            readed += cur_len;
        }
        in.close();
        if (this->size <= 255) {
            // 使用 TINYBLOB
            this->type = OL_TYPE_TINY_BLOB;
        }
        else if (this->size <= 65535) {
            // 使用 BLOB
            this->type = OL_TYPE_BLOB;
        }
        else if (this->size <= 16777215) {
            // 使用 MEDIUMBLOB
            this->type = OL_TYPE_MEDIUM_BLOB;
        }
        else if (this->size <= 4294967295) {
            // 使用 LONGBLOB
            this->type = OL_TYPE_LONG_BLOB;
        }
        else {
            // 文件太大，无法存储
            cerr << filename << " is too large to store in a BLOB!" << endl;
            Drop();
            return false;
        }
        return true;
    }

    bool OLData::SaveFile(const char* filename)
    {
        if (!filename || !data || size <= 0) return false;
        ofstream out(filename, ios::out | ios::binary);
        if (!out.is_open())
        {
            cerr << "open " << filename << " failed!" << endl;
            return false;
        }
        out.write(data, size);
        out.close();
        return true;
    }

    void OLData::Drop()
    {
        if (this->data)
        {
            delete data;
            data = nullptr;
        }
    }

#ifndef _WIN32
    static size_t Convart(char* from_char, char* to_char, char* in, size_t inlen, char* out, size_t outlen)
    {
        // 转换的上下文
        iconv_t cd;
        cd = iconv_open(to_char, from_char);
        if (cd == 0)
            return -1;
        memset(out, 0, outlen);
        char** pin = &in;
        char** pout = &out;
        // 返回转换的字节数，但是转化成GBK时经常不正确 >= 0成功
        size_t ret = iconv(cd, pin, &inlen, pout, &outlen);
        if (cd != 0)
            iconv_close(cd);
        return ret;
    }
#endif

    std::string OLData::UTF8ToGBK()
    {
        string gbk = "";
#ifdef _WIN32
        /// 1.UTF-8 转为unicode win -> utf16

        int len = MultiByteToWideChar(CP_UTF8, 0, data, -1, 0, 0);
        if (len <= 0) return gbk;
        wstring udata;
        udata.resize(len);
        // 多字节（Multi-Byte）字符串转换为宽字符（Wide Character）字符串
        MultiByteToWideChar(CP_UTF8, 0, data, -1, (wchar_t*)udata.data(), len);

        /// 2. unicode 转gbk
        len = WideCharToMultiByte(CP_ACP, 0, (wchar_t*)udata.data(), -1, 0, 0, 0, 0);
        if (len <= 0) return gbk;
        gbk.resize(len);
        WideCharToMultiByte(CP_ACP, 0, (wchar_t*)udata.data(), -1, (char*)gbk.data(), len, 0, 0);
#else
        gbk.resize(1024);
        int inlen = strlen(data);
        Convart((char*)"utf-8", (char*)"gbk", (char*)data, inlen, (char*)gbk.data(), gbk.size());
        int outlen = strlen(gbk.data());
        gbk.resize(outlen);
#endif
        return gbk;
    }
    
    std::string OLData::GBKToUTF8()
    {
        string utf8 = "";
#ifdef _WIN32
        /// 1.gbk 转为unicode win -> utf16
        int len = MultiByteToWideChar(CP_ACP, 0, data, -1, 0, 0);
        if (len <= 0) return utf8;

        wstring udata;
        udata.resize(len);
        MultiByteToWideChar(CP_ACP, 0, data, -1, (wchar_t*)udata.data(), len);

        /// 2. unicode 转utf8
        len = WideCharToMultiByte(CP_UTF8, 0, (wchar_t*)udata.data(), -1, 0, 0, 0, 0);
        if (len <= 0) return utf8;
        utf8.resize(len);
        WideCharToMultiByte(CP_UTF8, 0, (wchar_t*)udata.data(), -1, (char*)utf8.data(), len, 0, 0);
#else
        utf8.resize(1024);
        int inlen = strlen(data);
        Convart((char*)"gbk", (char*)"utf-8", (char*)data, inlen, (char*)utf8.data(), utf8.size());
        int outlen = strlen(utf8.data());
        utf8.resize(outlen);
#endif
        return utf8;
    }
}

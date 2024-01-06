#include "orion_link_db.h"

#include <mysql.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <climits>

using namespace std;

namespace ol
{

    bool OrionLinkDB::Init()
    {
        Close();
        mysql_ = mysql_init(0);
        if (!mysql_)
        {
            cerr << "mysql_init failed!" << endl;
            return false;
        }
        return true;
    }

    void OrionLinkDB::Close()
    {
        FreeResult();
        if (mysql_)
        {
            mysql_close(mysql_);
            mysql_ = nullptr;
        }
    }

    bool OrionLinkDB::Connect(const char* host, const char* user, const char* password,
        const char* db, unsigned short port, unsigned long flag)
    {
        if (!mysql_ && !Init())
        {
            cerr << "MySQL connect failed! MySQL is not init" << endl;
            return false;
        }
        if (!mysql_real_connect(mysql_, host, user, password, db, port, 0, flag))
        {
            cerr << "MySQL connect failed!" << mysql_error(mysql_) << endl;
            return false;
        }
        return true;
    }

    bool OrionLinkDB::Query(const char* sql, unsigned long sqllen)
    {
        if (!mysql_ || !sql)
        {
            cerr << "Query failed! mysql is null or sql is null" << endl;
            return false;
        }

        if (sqllen <= 0)
            sqllen = (unsigned long)strlen(sql);

        if (sqllen <= 0)
        {
            cerr << "Query sql is empty or wrong format" << endl;
            return false;
        }

        if (mysql_real_query(mysql_, sql, sqllen) != 0)
        {
            cerr << "Query failed! " << mysql_error(mysql_) << endl;
            return false;
        }

        return true;
    }

    bool OrionLinkDB::Options(orion_option opt, const void* arg)
    {
        if (!mysql_)
        {
            cerr << "Option failed! mysql is null" << endl;
            return false;
        }
        int ret = mysql_options(mysql_, (mysql_option)opt, arg);
        if (ret != 0)
        {
            cerr << "Option failed! " << mysql_error(mysql_) << endl;
            return false;
        }
        return true;
    }

    bool OrionLinkDB::SetConnectTimeout(int sec)
    {
        return Options(OL_OPT_CONNECT_TIMEOUT, &sec);
    }

    bool OrionLinkDB::SetReconnect(bool isre)
    {
        return Options(OL_OPT_RECONNECT, &isre);
    }

    bool OrionLinkDB::StoreResult()
    {
        if (!mysql_)
        {
            cerr << "StoreResult failed! mysql is null" << endl;
            return false;
        }
        FreeResult();
        result_ = mysql_store_result(mysql_);
        if (!result_)
        {
            cerr << "StoreResult failed! " <<mysql_error(mysql_) << endl;
            return false;
        }
        return true;
    }

    bool OrionLinkDB::UseResult()
    {
        if (!mysql_)
        {
            cerr << "UseResult failed! mysql is null" << endl;
            return false;
        }
        FreeResult();
        result_ = mysql_use_result(mysql_);
        if (!result_)
        {
            cerr << "UseResult failed! " << mysql_error(mysql_) << endl;
            return false;
        }
        return true;
    }

    void OrionLinkDB::FreeResult()
    {
        if (result_)
        {
            mysql_free_result(result_);
            result_ = nullptr;
        }
    }

    std::vector<OLData> OrionLinkDB::FetchRow()
    {
        std::vector<OLData> res;
        if (!result_)  return res;

        MYSQL_ROW row = mysql_fetch_row(result_);
        if (!row) return res;

        unsigned int column = mysql_num_fields(result_);
        unsigned long* lens = mysql_fetch_lengths(result_);
        for (unsigned int i = 0; i < column; i++)
        {
            OLData data;
            data.data = row[i];
            data.size = lens[i];
            auto field = mysql_fetch_field_direct(result_, i);
            data.type = (ol_field_types)field->type;
            res.push_back(data);
        }

        return res;
    }

    std::vector<char*> OrionLinkDB::FetchFieldsName()
    {
        std::vector<char*> res;
        if (!result_)  return res;

        MYSQL_FIELD *field = mysql_fetch_fields(result_);
        if (!field) return res;

        unsigned int column = mysql_num_fields(result_);
        for (unsigned int i = 0; i < column; i++)
        {
            char* data;
            data = field[i].name;
            res.push_back(data);
        }
        return res;
    }

    void OrionLinkDB::ShowFormatResult(int width, int limit, int offset)
    {
        if (!result_) return;

        if (width <= 0)
        {
            width = 20;
        }

        int show_row = 0;
        int begin = 0;
        int end = INT_MAX - 1;

        // 计算要显示的行范围
        if (limit > 0)
        {
            if (offset > 0)
            {
                begin = offset;
            }
            end = begin + limit;
        }

        auto column = FetchFieldsName();
        int column_size = (int)column.size();
        std::stringstream ss;

        // 顶部边框
        ss << "+";
        for (int i = 0; i < column_size; i++) {
            ss << std::string(width, '-') << "+";
        }
        ss << "\n";

        // 输出表头
        ss << "|";
        for (int i = 0; i < column_size; i++) {
            ss << std::left << std::setw(width) << column[i] << "|";
        }
        ss << "\n";

        // 下方分割线
        ss << "+";
        for (int i = 0; i < column_size; i++) {
            ss << std::string(width, '-') << "+";
        }
        ss << "\n";

        // 遍历数据行

        // 跳过前面行
        int current_row = 0;
        while (current_row < begin) {
            auto row = FetchRow();
            if (row.size() == 0) break;
            current_row++;
        }

        for (int i = begin; i < end; i++) 
        {
            auto row = FetchRow();
            if (row.size() == 0) break;
            ss << "|";
            for (int j = 0; j < row.size(); j++) 
            {
                switch (row[j].type)
                {
                case OL_TYPE_STRING:
                    ss << std::left << std::setw(width) << (row[j].data ? row[j].data : "NULL") << "|";
                    break;
                case OL_TYPE_BLOB:
                    if (row[j].data)
                        ss << std::left << std::setw(width) << "BLOB" << "|";
                    else
                        ss << std::left << std::setw(width) << "NULL" << "|";
                    break;
                default:
                    ss << std::left << std::setw(width) << (row[j].data ? row[j].data : "NULL") << "|";
                    break;
                }
            }
            ss << "\n";
        }

        // 底部边框
        ss << "+";
        for (int i = 0; i < column_size; i++) {
            ss << std::string(width, '-') << "+";
        }
        ss << "\n";

        // 打印结果
        std::cout << ss.str();
    }

    std::string OrionLinkDB::GetInsertSQL(const KVData& kv, const std::string& table)
    {
        std::string sql = "";
        if (kv.empty() || table.empty())
            return sql;
        /// insert into table_name(name, size) values('aaa.png', 1024) 
        sql += "insert into `";
        sql += table;
        sql += "` ";
        string keys = "";
        string values = "";
        for (const auto& iter : kv)
        {
            keys += "`";
            keys += iter.first;
            keys += "`,";

            values += "'";
            values += iter.second.data;
            values += "',";
        }
        // 去除多余逗号
        keys[keys.size() - 1] = ' ';
        values[values.size() - 1] = ' ';

        sql += "(";
        sql += keys;
        sql += ") values(";
        sql += values;
        sql += ")";

        return sql;
    }

    bool OrionLinkDB::Insert(const KVData& kv, const std::string& table)
    {
        if (!mysql_)
        {
            cerr << "Insert failed! mysql is null" << endl;
            return false;
        }
        string sql = move(GetInsertSQL(kv, table));
        if (sql.empty())
            return false;
        if (!Query(sql.c_str()))
            return false;
        int num = mysql_affected_rows(mysql_);
        if (num <= 0)
            return false;
        return true;
    }

    bool OrionLinkDB::InsertBin(const KVData& kv, const std::string& table)
    {
        std::string sql = "";
        if (kv.empty() || table.empty() || !mysql_)
            return false;

        sql += "insert into `";
        sql += table;
        sql += "` ";
        string keys = "";
        string values = "";

        /// 绑定字段
        std::vector<MYSQL_BIND> bind(kv.size() + 1);
        int i = 0;
        for (const auto& iter : kv)
        {
            keys += "`";
            keys += iter.first;
            keys += "`,";

            values += "?,";
            bind[i].buffer = (char*)iter.second.data;
            bind[i].buffer_length = iter.second.size;
            bind[i].buffer_type = (enum_field_types)iter.second.type;
            i++;
        }
        // 去除多余逗号
        keys[keys.size() - 1] = ' ';
        values[values.size() - 1] = ' ';

        sql += "(";
        sql += keys;
        sql += ") values(";
        sql += values;
        sql += ")";

        /// 预处理语句
        MYSQL_STMT* stmt = mysql_stmt_init(mysql_);
        if (!stmt)
        {
            cerr << "mysql_stmt_init failed! " << mysql_error(mysql_) << endl;
            return false;
        }
        if (mysql_stmt_prepare(stmt, sql.c_str(), sql.length()) != 0)
        {
            cerr << "mysql_stmt_prepare failed! " << mysql_error(mysql_) << endl;
            mysql_stmt_close(stmt);
            return false;
        }

        if (mysql_stmt_bind_param(stmt, bind.data()) != 0)
        {
            cerr << "mysql_stmt_bind_param failed! " << mysql_stmt_error(stmt) << endl;
            mysql_stmt_close(stmt);
            return false;
        }

        if (mysql_stmt_execute(stmt) != 0)
        {
            cerr << "mysql_stmt_execute failed! " << mysql_stmt_error(stmt) << endl;
            mysql_stmt_close(stmt);
            return false;
        }
        mysql_stmt_close(stmt);
        return true;
    }

    std::string OrionLinkDB::GetUpdateSQL(const KVData& kv, const std::string& table, const std::string& where)
    {
        std::string sql = "";
        if (kv.empty() || table.empty())
            return sql;
        sql += "update `";
        sql += table;
        sql += "` set";
        for (const auto& iter : kv)
        {
            sql += "`";
            sql += iter.first;
            sql += "` = ";
            sql += "'";
            sql += iter.second.data;
            sql += "',";
        }
        sql[sql.size() - 1] = ' ';
        sql += where;
        return sql;
    }

    int OrionLinkDB::Update(const KVData& kv, const std::string& table, const std::string& where)
    {
        if (!mysql_)
        {
            cerr << "Insert failed! mysql is null" << endl;
            return -1;
        }
        string sql = move(GetUpdateSQL(kv, table, where));
        if (sql.empty())
            return -1;
        if (!Query(sql.c_str()))
        {
            return -1;
        }
        return mysql_affected_rows(mysql_);
    }

    int OrionLinkDB::UpdateBin(const KVData& kv, const std::string& table, const std::string& where)
    {
        if (!mysql_ || kv.empty() || table.empty()) return -1;
        std::string sql = "";
        sql += "update `";
        sql += table;
        sql += "` set";
        std::vector<MYSQL_BIND> bind(kv.size() + 1);
        int i = 0;
        for (const auto& iter : kv)
        {
            sql += "`";
            sql += iter.first;
            sql += "` = ?,";
            bind[i].buffer = (char*)iter.second.data;
            bind[i].buffer_length = iter.second.size;
            bind[i].buffer_type = (enum_field_types)iter.second.type;
            i++;
        }
        sql[sql.size() - 1] = ' ';
        sql += where;
        /// 预处理语句
        MYSQL_STMT* stmt = mysql_stmt_init(mysql_);
        if (!stmt)
        {
            cerr << "mysql_stmt_init failed! " << mysql_error(mysql_) << endl;
            return -1;
        }
        if (mysql_stmt_prepare(stmt, sql.c_str(), sql.length()) != 0)
        {
            cerr << "mysql_stmt_prepare failed! " << mysql_error(mysql_) << endl;
            mysql_stmt_close(stmt);
            return -1;
        }

        if (mysql_stmt_bind_param(stmt, bind.data()) != 0)
        {
            cerr << "mysql_stmt_bind_param failed! " << mysql_stmt_error(stmt) << endl;
            mysql_stmt_close(stmt);
            return -1;
        }

        if (mysql_stmt_execute(stmt) != 0)
        {
            cerr << "mysql_stmt_execute failed! " << mysql_stmt_error(stmt) << endl;
            mysql_stmt_close(stmt);
            return -1;
        }
        int count = mysql_stmt_affected_rows(stmt);
        mysql_stmt_close(stmt);
        return count;
    }

    bool OrionLinkDB::StartTransaction()
    {
        if (!Query("begin"))
            return false;
        return Query("set autocommit=0");
    }

    bool OrionLinkDB::StopTransaction()
    {
        return Query("set autocommit=1");
    }

    bool OrionLinkDB::Commit()
    {
        StopTransaction();
        return Query("commit");
    }

    bool OrionLinkDB::Rollback()
    {
        return Query("rollback");
    }

    OLROWS OrionLinkDB::GetResult(const char* sql)
    {
        FreeResult();
        OLROWS rows;
        if (!Query(sql))
            return rows;
        if (!StoreResult())
            return rows;
        for (;;)
        {
            auto row = FetchRow();
            if (row.empty()) break;
            rows.push_back(row);
        }
        return rows;
    }

}

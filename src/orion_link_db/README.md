# OrionLinkDB

OrionLinkDB 是一个 C++ 库，提供了方便的接口来与 MySQL 数据库进行交互。它封装了常见的数据库操作，如连接、查询、插入、更新和事务管理等。

## 开始

以下指南将帮助您在本地机器上安装和运行 OrionLinkDB，用于开发和测试目的。

### 先决条件

在开始之前，您需要安装 MySQL 数据库和相应的 C++ 开发环境。

### 安装

1. 克隆仓库到您的本地机器：
   ```bash
   git https://github.com/1727370054/orion_link_db.git
   # 需要先安装MySQL依赖
   make
   make install
   ```
2. 根据您的系统和项目设置，编译项目。

## 使用方法

以下是 OrionLinkDB 的基本使用方法：

1. **初始化和连接数据库**

   ```cpp
   ol::OrionLinkDB db;
   db.Init();
   db.Connect("host", "user", "password", "db_name", 3306);
   ```

2. ##### 常用设置选项接口

   ``````c++
   /// 超时时间设置
   db.SetConnectTimeout(/*超时时间(s)*/);
   /// 设置自动重连
   db.SetReconnect(true);
   ``````

3. ##### **常规SQL语句**

   ```cpp
   db.Query("/*你的SQL语句*/");
   ```

4. ##### 插入数据（字符串数据）

   `````c++
   KVData kv;
   kv["字段名"] = "插入的数据";
   db.Insert(kv, "表名");
   `````

5. ##### 修改数据（字符串数据）

   ````c++
   KVData udata;
   udata["字段名"] = "修改的数据";
   ol.Update(udata, "表名", "where 条件"); /// 示例:where id=1
   ````

6. ##### 插入数据（二进制数据）

   `````c++
   string sql = "";
   sql = "create table if not exists video( \
   	   id int auto_increment,		    \
   	   name varchar(1024),			    \
   	   data mediumblob,		            \
   	   size int,					   \
   	   primary key(id))";
   if (ol.Query(sql.c_str(), sql.size()))
   {
   	cout << "Query success! " << endl;
   }
   OLData file;
   if (!file.LoadFile("../../source/OrionLinkLogo.png"))
   	return -1;
   kv["name"] = "OrionLinkLogo.png";
   kv["data"] = file;
   kv["size"] = &file.size;
   db.InsertBin(kv, "video"); // id = 1
   file.Drop();
   `````

7. ##### 修改数据（二进制数据）

   ````c++
   KVData udata;
   OLData file2;
   if (!file2.LoadFile("../../source/4.jpg"))
   	return -1;
   udata["data"] = file2;
   udata["name"] = "4.jpg";
   cout << "UpdateBin" << ol.UpdateBin(udata, "video", "where id =  3") << endl;
   file2.Drop();
   ````

8. ##### 下载数据中的二进制文件

   ``````c++
   for (;;)
   {
   	auto row = ol.FetchRow();
   	if (row.size() == 0) break;
   	row[2].SaveFile(row[1].data); /// row[2]对应表video的data字段， row[1].data对应name字段，可以自行指定文件名和路径
   }
   ``````

9. **获取查询结果**

   ```cpp
   auto rows = db.GetResult("SELECT * FROM your_table");
   db.FreeResult();
   /// or
   db.ShowFormatResult(); /// 格式化显示结果，第一个参数可指定表格列宽度
   ```

10. **事务处理**：

   ```cpp
   db.StartTransaction();
   // 执行事务相关操作
   db.Commit();
   ```

## 构建项目

`````bash
make
make install
`````

## 贡献

请阅读 CONTRIBUTING.md 了解为该项目做出贡献的流程。

## 版本控制

我们使用 Git 进行版本控制。有关更多信息，请参阅仓库中的提交历史。

## 作者

* **hwk**

# Linux 下 OrionLink 编译安装说明

## 1 依赖编译安装

```shell
# 先安装一些公共的工具
apt-get install perl g++ make automake libtool unzip
```

### zlib （protobuf，libevent） （压缩）

```shell
tar -xvf zlib-1.2.11.tar.gz
cd zlib-1.2.11/
./configure
make -j32
make install
# 安装在 /usr/local/include/ /usr/local/lib 目录下
```

### openssl （libevent） （安全加密）

```shell
tar -xvf openssl-1.1.1.tar.gz
cd openssl-1.1.1/
./config
make -j32
make install
# openssl 命令行 /usr/local/bin
#配置安装在 /usr/local/ssl
#头文件/usr/local/include/openssl
#so库文件/usr/local/lib
```

### protobuf （通信协议）

```shell
unzip protobuf-all-3.8.0.zip
cd protobuf-3.8.0/
./configure
make -j32
make install
#安装在 /usr/local/include/google/protobuf
# protoc /usr/local/bin
# so库文件 /usr/local/lib
```

### libevent （网络通信）

```shell
unzip libevent-master.zip
./autogen.sh
./configure
make -j32
make install
#安装在 /usr/local/lib /usr/local/include
```

### 安装 mysql

```shell
sudo apt-get install mysql-server
/etc/mysql/debian.cnf文件，在这个文件中有系统默认给我们分配的用户名和密码
mysql -u debian-sys-maint -p
set password for 'root'@'localhost' = password('yourpass')
```



## 2 安装运行OrionLink 

### 预备工作

+ 生成openssl证书和私钥

```shell

```

+ 先进入 src/api_gateway 目录

```shell
cd src/api_gateway
```

+ 注释掉代码

````c++
````

+ 进入bin目录开始编译

````shell
sudo build_all.sh
````

### 运行

+ 添加数据库连接配置文件

````shell
# 先进入mysql客户端创建orion_link数据库 
sudo build_mysql_conf # 填写用户名、密码、数据库名称、端口号
````

+ 先运行注册中心、网关、鉴权中心和配置中心

```shell
sudo start_register_server
sudo start_config_server
sudo start_api_gateway
sudo start_auth
```

+ 运行云盘客户端、注册==root==用户
+ 运行配置管理工具，添加网关配置

````
````


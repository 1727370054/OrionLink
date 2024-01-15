# Linux 下 XMS 编译安装说明

## 1 依赖编译安装 (tools 目录下)

    # 先安装一些公共的工具
    apt-get install perl g++ make automake libtool unzip

### zlib （protobuf，libevent） （压缩）

    tar -xvf zlib-1.2.11.tar.gz
    cd zlib-1.2.11/
    ./configure
    make -j32
    make install
    # 安装在 /usr/local/include/ /usr/local/lib 目录下

### openssl （libevent） （安全加密）

    tar -xvf openssl-1.1.1.tar.gz
    cd openssl-1.1.1/
    ./config
    make -j32
    make install
    # openssl 命令行 /usr/local/bin
    #配置安装在 /usr/local/ssl
    #头文件/usr/local/include/openssl
    #so库文件/usr/local/lib

### protobuf （通信协议）

    unzip protobuf-all-3.8.0.zip
    cd protobuf-3.8.0/
    ./configure
    make -j32
    make install
    #安装在 /usr/local/include/google/protobuf
    # protoc /usr/local/bin
    # so库文件 /usr/local/lib

### libevent （网络通信）

    unzip libevent-master.zip
    ./autogen.sh
    ./configure
    make -j32
    make install
    #安装在 /usr/local/lib /usr/local/include

## platform （公共通信库）编译安装 依赖 libevent protobuf openssl

    cd src/platform
    # 生成proto对应的c++代码
    make proto
    make -j32
    make install
    # 安装到 /usr/lib/libplatform.so

## orion_link_db （数据库 DAO） 编译安装

    apt-get install libmysqlclient-dev
    make -j32
    # 安装在 /usr/lib/liboldb.so

## 安装 mysql

    sudo apt-get install mysql-server
    /etc/mysql/debian.cnf文件，在这个文件中有系统默认给我们分配的用户名和密码
    mysql -u debian-sys-maint -p
    set password for 'root'@'localhost' = password('yourpass')

## register_server （注册中心）编译安装 依赖 xplatform

    cd src/register_server
    make -j32
    stop_register_server
    make install
    start_register_server

    #后面需要做成守护进程，并添加watchdog
    # 第一次运行需要输入数据库信息，数据库ip，用户，密码（暂时没有加密存储，后面考虑用aes做加密）

## config_server(配置中心) 编译安装，依赖 LXMysql xplatform register_client（源码编入）

    cd src/config_server
    make -j32
    stop_config_server
    make install
    start_config_server

## api_gateway （网关）编译安装，依赖 platform register_client（源码编入） config_client（源码编入）

    cd src/api_gateway
    make -j32
    ./api_gateway  &
    #后面需要做成守护进程，并添加watchdog

## test_pb_service (测试微服务) 依赖 xplatform register_client（源码编入） config_client（源码编入）

    cd src/test_pb_service
    make -j32
    ./test_pb_service  &

## test_service_client (测试微服务的客户端) 依赖 xplatform register_client（源码编入） config_client（源码编入）

    cd src/test_service_client
    make -j32
    ./test_service_client &

#!/bin/bash

# 获取脚本所在目录
SCRIPT_DIR=$(dirname "$0")

# 使用 protoc 编译 .proto 文件，指定输出路径为当前目录
protoc -I="$SCRIPT_DIR" --cpp_out="$SCRIPT_DIR" "$SCRIPT_DIR/msg_comm.proto"
protoc -I="$SCRIPT_DIR" --cpp_out="$SCRIPT_DIR" "$SCRIPT_DIR/msg_type.proto"
#!/bin/bash
protoc -I=./ --cpp_out=./ msg_comm.proto
protoc -I=./ --cpp_out=./ msg_type.proto

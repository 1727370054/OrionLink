// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: msg_type.proto

#include "msg_type.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace msg {
}  // namespace msg
static const ::_pb::EnumDescriptor* file_level_enum_descriptors_msg_5ftype_2eproto[1];
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_msg_5ftype_2eproto = nullptr;
const uint32_t TableStruct_msg_5ftype_2eproto::offsets[1] = {};
static constexpr ::_pbi::MigrationSchema* schemas = nullptr;
static constexpr ::_pb::Message* const* file_default_instances = nullptr;

const char descriptor_table_protodef_msg_5ftype_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\016msg_type.proto\022\003msg*\375\003\n\007MsgType\022\023\n\017NON"
  "E_DO_NOT_USE\020\000\022\021\n\rMSG_LOGIN_REQ\020\001\022\021\n\rMSG"
  "_LOGIN_RES\020\002\022\017\n\013MSG_DIR_REQ\020\003\022\017\n\013MSG_DIR"
  "_RES\020\004\022\024\n\020MSG_REGISTER_REQ\020\005\022\024\n\020MSG_REGI"
  "STER_RES\020\006\022\027\n\023MSG_GET_SERVICE_REQ\020\007\022\027\n\023M"
  "SG_GET_SERVICE_RES\020\010\022\027\n\023MSG_SAVE_CONFIG_"
  "REQ\020\t\022\027\n\023MSG_SAVE_CONFIG_RES\020\n\022\027\n\023MSG_LO"
  "AD_CONFIG_REQ\020\013\022\027\n\023MSG_LOAD_CONFIG_RES\020\014"
  "\022\033\n\027MSG_LOAD_ALL_CONFIG_REQ\020\r\022\033\n\027MSG_LOA"
  "D_ALL_CONFIG_RES\020\016\022\026\n\022MSG_DEL_CONFIG_REQ"
  "\020\017\022\026\n\022MSG_DEL_CONFIG_RES\020\020\022\024\n\020MSG_ADD_US"
  "ER_REQ\020\021\022\024\n\020MSG_ADD_USER_RES\020\022\022\024\n\017MSG_AD"
  "D_LOG_REQ\020\322\001\022\023\n\rMSG_HEART_REQ\020\376\377\003\022\022\n\014MSG"
  "_MAX_TYPE\020\377\377\003b\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_msg_5ftype_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_msg_5ftype_2eproto = {
    false, false, 541, descriptor_table_protodef_msg_5ftype_2eproto,
    "msg_type.proto",
    &descriptor_table_msg_5ftype_2eproto_once, nullptr, 0, 0,
    schemas, file_default_instances, TableStruct_msg_5ftype_2eproto::offsets,
    nullptr, file_level_enum_descriptors_msg_5ftype_2eproto,
    file_level_service_descriptors_msg_5ftype_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_msg_5ftype_2eproto_getter() {
  return &descriptor_table_msg_5ftype_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_msg_5ftype_2eproto(&descriptor_table_msg_5ftype_2eproto);
namespace msg {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* MsgType_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_msg_5ftype_2eproto);
  return file_level_enum_descriptors_msg_5ftype_2eproto[0];
}
bool MsgType_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 210:
    case 65534:
    case 65535:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace msg
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>

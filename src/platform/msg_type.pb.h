// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: msg_type.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_msg_5ftype_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_msg_5ftype_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021011 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_msg_5ftype_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_msg_5ftype_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_msg_5ftype_2eproto;
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE
namespace msg {

enum MsgType : int {
  NONE_DO_NOT_USE = 0,
  MSG_LOGIN_REQ = 1,
  MSG_LOGIN_RES = 2,
  MSG_DIR_REQ = 3,
  MSG_DIR_RES = 4,
  MSG_REGISTER_REQ = 5,
  MSG_REGISTER_RES = 6,
  MSG_GET_SERVICE_REQ = 7,
  MSG_GET_SERVICE_RES = 8,
  MSG_SAVE_CONFIG_REQ = 9,
  MSG_SAVE_CONFIG_RES = 10,
  MSG_LOAD_CONFIG_REQ = 11,
  MSG_LOAD_CONFIG_RES = 12,
  MSG_LOAD_ALL_CONFIG_REQ = 13,
  MSG_LOAD_ALL_CONFIG_RES = 14,
  MSG_DEL_CONFIG_REQ = 15,
  MSG_DEL_CONFIG_RES = 16,
  MSG_ADD_USER_REQ = 17,
  MSG_ADD_USER_RES = 18,
  MSG_ADD_LOG_REQ = 210,
  MSG_HEART_REQ = 65534,
  MSG_MAX_TYPE = 65535,
  MsgType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  MsgType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool MsgType_IsValid(int value);
constexpr MsgType MsgType_MIN = NONE_DO_NOT_USE;
constexpr MsgType MsgType_MAX = MSG_MAX_TYPE;
constexpr int MsgType_ARRAYSIZE = MsgType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* MsgType_descriptor();
template<typename T>
inline const std::string& MsgType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, MsgType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function MsgType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    MsgType_descriptor(), enum_t_value);
}
inline bool MsgType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, MsgType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<MsgType>(
    MsgType_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace msg

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::msg::MsgType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::msg::MsgType>() {
  return ::msg::MsgType_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_msg_5ftype_2eproto

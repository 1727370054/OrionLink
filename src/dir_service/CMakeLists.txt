aux_source_directory(. SRC_LIST)
add_executable(dir_service ${SRC_LIST})
target_link_libraries(dir_service event pthread platform protobuf ssl register_client disk_pb)
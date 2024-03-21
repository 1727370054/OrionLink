aux_source_directory(. SRC_LIST)
add_executable(upload_service ${SRC_LIST})
target_link_libraries(upload_service event pthread platform protobuf ssl disk_pb register_client)
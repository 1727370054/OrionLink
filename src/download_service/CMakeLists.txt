aux_source_directory(. SRC_LIST)
add_executable(download_service ${SRC_LIST})
target_link_libraries(download_service event pthread platform protobuf ssl register_client disk_pb)
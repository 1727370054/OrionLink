aux_source_directory(. SRC_LIST)
add_executable(log ${SRC_LIST})
target_link_libraries(log event pthread platform protobuf ssl register_client oldb)
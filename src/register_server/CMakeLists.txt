aux_source_directory(. SRC_LIST)
add_executable(register_server ${SRC_LIST})
target_link_libraries(register_server event pthread platform protobuf ssl)
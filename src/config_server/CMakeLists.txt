aux_source_directory(. SRC_LIST)
add_executable(config_server ${SRC_LIST})
target_link_libraries(config_server event pthread platform protobuf ssl oldb register_client)
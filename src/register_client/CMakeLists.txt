aux_source_directory(. SRC_LIST)
add_library(register_client SHARED ${SRC_LIST})
target_link_libraries(register_client event pthread platform protobuf ssl)
aux_source_directory(. SRC_LIST)
add_library(config_client SHARED ${SRC_LIST})
target_link_libraries(config_client event pthread platform protobuf ssl register_client)
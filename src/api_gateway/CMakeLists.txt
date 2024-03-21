aux_source_directory(. SRC_LIST)
add_executable(api_gateway ${SRC_LIST})
target_link_libraries(api_gateway event pthread platform protobuf ssl register_client config_client)
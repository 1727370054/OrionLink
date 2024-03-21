execute_process(
    COMMAND bash ${PROJECT_SOURCE_DIR}/src/platform/build_msg.sh
)
aux_source_directory(. SRC_LIST)
add_library(platform SHARED ${SRC_LIST})
target_link_libraries(platform event pthread event_openssl ssl)
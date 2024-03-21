execute_process(
    COMMAND bash ${PROJECT_SOURCE_DIR}/src/disk_proto/build_msg.sh
)

set(TARGET_DIR "${PROJECT_SOURCE_DIR}/include/orion_link")
file(MAKE_DIRECTORY ${TARGET_DIR})
file(GLOB HEADER_FILES "*.h")
file(COPY ${HEADER_FILES} DESTINATION ${TARGET_DIR})

aux_source_directory(. SRC_LIST)
add_library(disk_pb SHARED ${SRC_LIST})
target_link_libraries(disk_pb protobuf)
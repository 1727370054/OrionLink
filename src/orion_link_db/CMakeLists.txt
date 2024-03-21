aux_source_directory(. SRC_LIST)
add_library(oldb SHARED ${SRC_LIST})
target_link_libraries(oldb pthread mysqlclient)
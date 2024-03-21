cmake_minimum_required(VERSION 3.0)
project(OrionLink)

# 匹配所有的.h文件
file(GLOB_RECURSE HEADER_FILES "${PROJECT_SOURCE_DIR}/src/**/*.h")

# 指定头文件应该被拷贝到的目标目录
set(TARGET_DIR "${PROJECT_SOURCE_DIR}/include/orion_link")

file(MAKE_DIRECTORY ${TARGET_DIR})

set(EXCLUDE_DIRS "comm_proto" "config_gui" "disk_client_gui") # 定义排除目录列表

foreach(file_path ${HEADER_FILES})
  # 默认设置为拷贝该文件
  set(COPY_FILE TRUE)

  # 遍历排除目录列表
  foreach(exclude_dir ${EXCLUDE_DIRS})
    if(file_path MATCHES ${exclude_dir})
      set(COPY_FILE FALSE)
      break() # 如果匹配到排除目录，就设置不拷贝，并跳出循环
    endif()
  endforeach()

  if(COPY_FILE)
    file(COPY "${file_path}" DESTINATION "${TARGET_DIR}")
  endif()
endforeach()


# 设置release版本还是debug版本
if(${CMAKE_BUILD_TYPE} MATCHES "Release")
    MESSAGE(STATUS "Release版本")
    SET(BuildType "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O2")
else()
    SET(BuildType "Debug")
    MESSAGE(STATUS "Debug版本")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall -O2")
endif()

message(STATUS "CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS})

set(CMAKE_CXX_STANDARD 14)

# 检测编译器(禁用警告)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # GCC 和 Clang
    add_compile_options(-w)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # MSVC
    add_compile_options(/W0)
endif()

# 设置项目可执行文件输出的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# 设置项目库文件输出的路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/include/orion_link)
include_directories(/usr/include/mysql)
link_directories(${PROJECT_SOURCE_DIR}/lib)
add_subdirectory(src)

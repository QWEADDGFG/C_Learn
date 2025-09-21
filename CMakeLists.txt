cmake_minimum_required(VERSION 3.10)
project(demo)

include_directories(${PROJECT_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 找到 pthread 库
find_package(Threads REQUIRED)

# 编译两个可执行文件
# add_executable(demo src/2_getip.c)
# add_executable(3_client src/3_client.c)
# add_executable(3_server src/3_server.c)
add_executable(4_AQ src/4_AQ.c)
add_executable(4_AZ src/4_AZ.c)
# 链接 pthread
# target_link_libraries(pc Threads::Threads)

# 调试信息
set(CMAKE_BUILD_TYPE Debug)
cmake_minimum_required(VERSION 3.10)
project(demo)

include_directories(${PROJECT_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 找到 pthread
find_package(Threads REQUIRED)

# 编译两个可执行文件
# add_executable(1_a src/1_a.c)
# add_executable(1_b src/1_b.c)
add_executable(2_flag src/2_flag.c)

# 链接 pthread
target_link_libraries(2_flag Threads::Threads)


# 调试信息
set(CMAKE_BUILD_TYPE Debug)
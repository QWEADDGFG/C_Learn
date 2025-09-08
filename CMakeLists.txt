cmake_minimum_required(VERSION 3.10)
project(demo)

include_directories(${PROJECT_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 找到 pthread
find_package(Threads REQUIRED)

# 编译两个可执行文件
# add_executable(1_a src/1_a.c)
# add_executable(1_b src/1_b.c)
add_executable(6_cnode src/6_cnode.c)

# 链接 pthread
# target_link_libraries(2_pthread Threads::Threads)


# 调试信息
set(CMAKE_BUILD_TYPE Debug)
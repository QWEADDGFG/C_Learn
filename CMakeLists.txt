cmake_minimum_required(VERSION 3.10)

project (demo)
include_directories(${PROJECT_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)


add_executable(
    demo           # 可执行文件名称
    ${SRC_LIST}     # 源文件列表
)

set(CMAKE_BUILD_TYPE "Debug") #生成可以debug的可执行文件

# 把 src 目录下的所有 C++ 源文件编译成一个名为 demo 的可执行文件，头文件搜索路径指向 include，输出目录为 bin

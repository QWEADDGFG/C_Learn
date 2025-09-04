cmake_minimum_required(VERSION 3.10)

project (demo)
include_directories(${PROJECT_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)


# add_executable(
#     demo1
#     demo2           # 可执行文件名称
#     ${SRC_LIST}     # 源文件列表
# )

# 原始demo程序
add_executable(1_a src/1_a.c)
add_executable(1_b src/1_b.c)

# 成绩转换程序
# add_executable(grade_converter src/grade_converter.cpp)

set(CMAKE_BUILD_TYPE "Debug") #生成可以debug的可执行文件

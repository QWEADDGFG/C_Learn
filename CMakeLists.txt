cmake_minimum_required(VERSION 3.10)

project (demo)
include_directories(${PROJECT_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# aux_source_directory(${PROJECT_SOURCE_DIR}/linux SRC_LIST)


# add_executable(
#     demo           # 可执行文件名称
#     ${SRC_LIST}     # 源文件列表
# )

# 原始demo程序
# add_executable(demo src/main.c)
add_executable(to_up_rw src/to_up_rw.c)

# 成绩转换程序
# add_executable(grade_converter src/grade_converter.cpp)

set(CMAKE_BUILD_TYPE "Debug") #生成可以debug的可执行文件

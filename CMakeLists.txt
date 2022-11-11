cmake_minimum_required(VERSION 3.0)  # cmake -G "MinGW/Unit Makefiles" ..
project(BOOKMARK)
set(CMAKE_CXX_STANDARD 20)
# 头文件目录
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/include")
# 源文件目录
AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/src/src" DIR_SRCS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
# 生成可执行文件
add_executable(bookmark ./src/main.cc ${DIR_SRCS})
target_link_libraries(bookmark stdc++fs)
# 增加测试工程
add_subdirectory(test)
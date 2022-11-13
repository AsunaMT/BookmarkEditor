cmake_minimum_required(VERSION 3.0)  # cmake .. -G "Unix Makefiles" 
project(BOOKMARK)
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_FLAGS "-O3")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/include")

AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/src/src" DIR_SRCS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(bookmark ./src/main.cc ${DIR_SRCS})
target_link_libraries(bookmark stdc++fs)

add_subdirectory(test)
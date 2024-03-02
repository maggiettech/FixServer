cmake_minimum_required(VERSION 3.27)
project(FixServer)

set(CMAKE_CXX_STANDARD 20)

add_executable(FixServer main.cpp)

find_package(quickfix CONFIG REQUIRED)
target_link_libraries(FixServer PRIVATE quickfix)
cmake_minimum_required(VERSION 2.8.9)
project(MyApplication CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")

add_subdirectory(src)

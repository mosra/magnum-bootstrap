cmake_minimum_required(VERSION 2.8.8)
project(MyApplication)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")

add_subdirectory(src)

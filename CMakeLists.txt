cmake_minimum_required(VERSION 3.4)
project(MyApplication)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules/" ${CMAKE_MODULE_PATH})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)

add_subdirectory(src)

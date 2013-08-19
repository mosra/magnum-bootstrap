find_package(Magnum REQUIRED WindowlessGlxApplication)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CORRADE_CXX_FLAGS}")
include_directories(${MAGNUM_INCLUDE_DIRS} ${MAGNUM_WINDOWLESSAPPLICATION_INCLUDE_DIRS})

add_executable(MyApplication MyApplication.cpp)
target_link_libraries(MyApplication
    ${MAGNUM_LIBRARIES}
    ${MAGNUM_WINDOWLESSAPPLICATION_LIBRARIES})

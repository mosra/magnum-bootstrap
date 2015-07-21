find_package(Magnum REQUIRED
    Sdl2Application)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CORRADE_CXX_FLAGS}")
include_directories(${MAGNUM_INCLUDE_DIRS} ${MAGNUM_APPLICATION_INCLUDE_DIRS})

add_executable(MyApplication MyApplication.cpp)
target_link_libraries(MyApplication
    ${MAGNUM_APPLICATION_LIBRARIES}
    ${MAGNUM_LIBRARIES})

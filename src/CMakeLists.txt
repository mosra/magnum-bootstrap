find_package(Magnum REQUIRED
    SceneGraph
    GlutApplication)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CORRADE_CXX_FLAGS}")
include_directories(${MAGNUM_INCLUDE_DIRS} ${MAGNUM_APPLICATION_INCLUDE_DIRS})

add_executable(MyApplication MyApplication.cpp)
target_link_libraries(MyApplication
    ${MAGNUM_LIBRARIES}
    ${MAGNUM_SCENEGRAPH_LIBRARIES}
    ${MAGNUM_APPLICATION_LIBRARIES})

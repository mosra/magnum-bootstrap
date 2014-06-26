find_package(Magnum REQUIRED)

if(CORRADE_TARGET_APPLE)
    find_package(Magnum REQUIRED WindowlessCglApplication)
elseif(CORRADE_TARGET_UNIX)
    find_package(Magnum REQUIRED WindowlessGlxApplication)
elseif(CORRADE_TARGET_WINDOWS)
    find_package(Magnum REQUIRED WindowlessWglApplication)
else()
    message(FATAL_ERROR "No windowless application available on this platform")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CORRADE_CXX_FLAGS}")
include_directories(${MAGNUM_INCLUDE_DIRS} ${MAGNUM_WINDOWLESSAPPLICATION_INCLUDE_DIRS})

add_executable(MyApplication MyApplication.cpp)
target_link_libraries(MyApplication
    ${MAGNUM_LIBRARIES}
    ${MAGNUM_WINDOWLESSAPPLICATION_LIBRARIES})

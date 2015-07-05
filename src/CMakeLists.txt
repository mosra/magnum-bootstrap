find_package(Magnum REQUIRED Sdl2Application)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CORRADE_CXX_FLAGS}")
include_directories(${MAGNUM_INCLUDE_DIRS} ${MAGNUM_APPLICATION_INCLUDE_DIRS})

add_executable(MyApplication WIN32 MyApplication.cpp)
target_link_libraries(MyApplication
    ${MAGNUM_APPLICATION_LIBRARIES}
    ${MAGNUM_LIBRARIES})

if(CORRADE_TARGET_EMSCRIPTEN)
    install(TARGETS MyApplication DESTINATION ${CMAKE_INSTALL_PREFIX})
    install(FILES MyApplication.html EmscriptenApplication.js WebApplication.css DESTINATION ${CMAKE_INSTALL_PREFIX})
endif()

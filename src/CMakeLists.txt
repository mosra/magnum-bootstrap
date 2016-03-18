find_package(Magnum REQUIRED Sdl2Application)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

add_executable(MyApplication MyApplication.cpp)
target_link_libraries(MyApplication
    Magnum::Application
    Magnum::Magnum)

if(CORRADE_TARGET_EMSCRIPTEN)
    install(TARGETS MyApplication DESTINATION ${CMAKE_INSTALL_PREFIX})
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/MyApplication.js.mem DESTINATION ${CMAKE_INSTALL_PREFIX} OPTIONAL)
    install(FILES MyApplication.html EmscriptenApplication.js WebApplication.css DESTINATION ${CMAKE_INSTALL_PREFIX})
endif()

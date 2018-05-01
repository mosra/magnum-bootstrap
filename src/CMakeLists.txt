find_package(Magnum REQUIRED GL Sdl2Application)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

add_executable(MyApplication MyApplication.cpp)
target_link_libraries(MyApplication PRIVATE
    Magnum::Application
    Magnum::GL
    Magnum::Magnum)

if(CORRADE_TARGET_EMSCRIPTEN)
    install(TARGETS MyApplication DESTINATION ${CMAKE_INSTALL_PREFIX})
    install(FILES
        MyApplication.html
        EmscriptenApplication.js
        WebApplication.css
        DESTINATION ${CMAKE_INSTALL_PREFIX})
    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/MyApplication.js.mem
        ${CMAKE_CURRENT_BINARY_DIR}/MyApplication.wasm
        DESTINATION ${CMAKE_INSTALL_PREFIX} OPTIONAL)
endif()

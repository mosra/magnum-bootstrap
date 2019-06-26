find_package(Magnum REQUIRED GL)

if(MAGNUM_TARGET_HEADLESS OR CORRADE_TARGET_EMSCRIPTEN)
    find_package(Magnum REQUIRED WindowlessEglApplication)
elseif(CORRADE_TARGET_IOS)
    find_package(Magnum REQUIRED WindowlessIosApplication)
elseif(CORRADE_TARGET_APPLE)
    find_package(Magnum REQUIRED WindowlessCglApplication)
elseif(CORRADE_TARGET_UNIX)
    find_package(Magnum REQUIRED WindowlessGlxApplication)
elseif(CORRADE_TARGET_WINDOWS)
    if(NOT MAGNUM_TARGET_GLES OR MAGNUM_TARGET_DESKTOP_GLES)
        find_package(Magnum REQUIRED WindowlessWglApplication)
    else()
        find_package(Magnum REQUIRED WindowlessWindowsEglApplication)
    endif()
else()
    message(FATAL_ERROR "No windowless application available on this platform")
endif()

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

add_executable(MyApplication MyApplication.cpp)
target_link_libraries(MyApplication PRIVATE
    Magnum::GL
    Magnum::Magnum
    Magnum::WindowlessApplication)
if(CORRADE_TARGET_IOS)
    set_target_properties(MyApplication PROPERTIES
        MACOSX_BUNDLE ON
        MACOSX_BUNDLE_GUI_IDENTIFIER "cz.mosra.magnum.MyApplication"
        XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "YES")
elseif(CORRADE_TARGET_EMSCRIPTEN)
    install(TARGETS MyApplication DESTINATION ${MAGNUM_DEPLOY_PREFIX})
    install(FILES
        MyApplication.html
        ${MAGNUM_WINDOWLESSEMSCRIPTENAPPLICATION_JS}
        ${MAGNUM_WEBAPPLICATION_CSS}
        DESTINATION ${MAGNUM_DEPLOY_PREFIX})
    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/MyApplication.js.mem
        ${CMAKE_CURRENT_BINARY_DIR}/MyApplication.wasm
        DESTINATION ${MAGNUM_DEPLOY_PREFIX} OPTIONAL)
endif()

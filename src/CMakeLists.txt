find_package(Magnum REQUIRED GL)

if(MAGNUM_TARGET_HEADLESS)
    find_package(Magnum REQUIRED WindowlessEglApplication)
elseif(CORRADE_TARGET_IOS)
    find_package(Magnum REQUIRED WindowlessIosApplication)
elseif(CORRADE_TARGET_APPLE)
    find_package(Magnum REQUIRED WindowlessCglApplication)
elseif(CORRADE_TARGET_UNIX)
    if(NOT MAGNUM_TARGET_GLES OR MAGNUM_TARGET_DESKTOP_GLES)
        find_package(Magnum REQUIRED WindowlessGlxApplication)
    else()
        find_package(Magnum REQUIRED WindowlessEglApplication)
    endif()
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
endif()

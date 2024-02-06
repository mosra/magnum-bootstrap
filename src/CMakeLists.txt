find_package(Magnum REQUIRED GL)

if(MAGNUM_TARGET_EGL)
    find_package(Magnum REQUIRED WindowlessEglApplication)
elseif(CORRADE_TARGET_IOS)
    find_package(Magnum REQUIRED WindowlessIosApplication)
elseif(CORRADE_TARGET_APPLE)
    find_package(Magnum REQUIRED WindowlessCglApplication)
elseif(CORRADE_TARGET_UNIX)
    find_package(Magnum REQUIRED WindowlessGlxApplication)
elseif(CORRADE_TARGET_WINDOWS)
    find_package(Magnum REQUIRED WindowlessWglApplication)
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

# Make the executable a default target to build & run in Visual Studio
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MyApplication)

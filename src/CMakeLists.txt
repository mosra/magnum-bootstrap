find_package(Magnum REQUIRED GL)

if(NOT CORRADE_TARGET_ANDROID)
    find_package(Magnum REQUIRED Sdl2Application)
else()
    find_package(Magnum REQUIRED AndroidApplication)
endif()

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

if(NOT CORRADE_TARGET_ANDROID)
    add_executable(MyApplication MyApplication.cpp)
else()
    add_library(MyApplication SHARED MyApplication.cpp)
endif()

target_link_libraries(MyApplication PRIVATE
    Magnum::Application
    Magnum::GL
    Magnum::Magnum)

# Gradle-free Android build
if(CORRADE_TARGET_ANDROID AND CMAKE_ANDROID_NDK)
    include(${PROJECT_SOURCE_DIR}/toolchains/modules/UseAndroid.cmake)
    android_create_apk(MyApplication main/AndroidManifest.xml)
endif()

# Make the executable a default target to build & run in Visual Studio
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MyApplication)

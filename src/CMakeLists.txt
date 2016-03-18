find_package(Magnum REQUIRED)

if(NOT CORRADE_TARGET_ANDROID)
    find_package(Magnum REQUIRED Sdl2Application)
else()
    find_package(Magnum REQUIRED AndroidApplication)
endif()

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

if(NOT CORRADE_TARGET_ANDROID)
    add_executable(MyApplication MyApplication.cpp)
else()
    file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}")
    add_library(MyApplication SHARED MyApplication.cpp)
endif()

target_link_libraries(MyApplication
    Magnum::Application
    Magnum::Magnum)

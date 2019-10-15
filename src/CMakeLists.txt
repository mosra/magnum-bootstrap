find_package(Magnum REQUIRED
    GL
    SceneGraph
    Sdl2Application)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

add_executable(MyApplication MyApplication.cpp)
target_link_libraries(MyApplication PRIVATE
    Magnum::Application
    Magnum::GL
    Magnum::Magnum
    Magnum::SceneGraph)

# Make the executable a default target to build & run in Visual Studio
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MyApplication)

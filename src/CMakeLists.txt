find_package(Magnum REQUIRED
    SceneGraph
    Sdl2Application)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

add_executable(MyApplication MyApplication.cpp)
target_link_libraries(MyApplication
    Magnum::Application
    Magnum::Magnum
    Magnum::SceneGraph)

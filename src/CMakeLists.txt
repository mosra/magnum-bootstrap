# wxWidgets 3.0 needs -std=gnu++11 instead of -std=c++11 in order to compile
# correctly
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS ON)

find_package(Magnum REQUIRED GL)

if(CORRADE_TARGET_WINDOWS)
    find_package(Magnum REQUIRED WglContext)
elseif(CORRADE_TARGET_APPLE)
    find_package(Magnum REQUIRED CglContext)
elseif(CORRADE_TARGET_UNIX)
    find_package(Magnum REQUIRED GlxContext)
else()
    message(FATAL_ERROR "No context available on this platform")
endif()

find_package(wxWidgets REQUIRED base core gl)
include(${wxWidgets_USE_FILE})

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

add_executable(MyApplication MyApplication.cpp)
target_link_libraries(MyApplication PRIVATE
    Magnum::GLContext
    Magnum::GL
    Magnum::Magnum
    ${wxWidgets_LIBRARIES})

# Make the executable a default target to build & run in Visual Studio
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MyApplication)

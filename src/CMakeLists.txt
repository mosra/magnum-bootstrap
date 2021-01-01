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

# Supply additional names for the wx-config tool that CMake's FindwxWidgets
# doesn't recognize. If you get
#   Could NOT find wxWidgets (missing: wxWidgets_LIBRARIES
#     wxWidgets_INCLUDE_DIRS)
# and your wx-config isn't listed in find_program(wxWidgets_CONFIG_EXECUTABLE)
# of CMake's FindwxWidgets.cmake module, add it here and please open an issue
# on the magnum-bootstrap repo as well. Thank you!
set(ENV{WX_CONFIG} wx-config-gtk3)

find_package(wxWidgets REQUIRED base core gl)
include(${wxWidgets_USE_FILE})

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

add_executable(MyApplication MyApplication.cpp)
target_include_directories(MyApplication PRIVATE
    ${wxWidgets_INCLUDE_DIRS})
target_link_libraries(MyApplication PRIVATE
    Magnum::GLContext
    Magnum::GL
    Magnum::Magnum
    ${wxWidgets_LIBRARIES})

# Make the executable a default target to build & run in Visual Studio
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MyApplication)

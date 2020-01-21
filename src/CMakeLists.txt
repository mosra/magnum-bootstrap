find_package(Magnum REQUIRED GL)

#[[

if(MAGNUM_TARGET_GLES AND NOT MAGNUM_TARGET_DESKTOP_GLES)
    find_package(Magnum REQUIRED EglContext)
elseif(CORRADE_TARGET_WINDOWS)
    find_package(Magnum REQUIRED WglContext)
elseif(CORRADE_TARGET_APPLE)
    find_package(Magnum REQUIRED CglContext)
elseif(CORRADE_TARGET_UNIX)
    find_package(Magnum REQUIRED GlxContext)
else()
    message(FATAL_ERROR "Magnum context creation is not supported on this platform")
endif()

]]

#set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(MyApplication MyApplication.cpp)
target_link_libraries(MyApplication PRIVATE
        #Magnum::GLContext
        Magnum::GL
        Magnum::Magnum
        ${GTKMM_LIBRARIES})

# Make the executable a default target to build & run in Visual Studio
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MyApplication)

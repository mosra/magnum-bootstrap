find_package(Magnum REQUIRED
    Sdl2Application)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CORRADE_CXX_FLAGS}")
include_directories(${MAGNUM_INCLUDE_DIRS} ${MAGNUM_APPLICATION_INCLUDE_DIRS})

if(CORRADE_TARGET_WINDOWS_RT)
    # The user has to provide the signing certificate
    set(SIGNING_CERTIFICATE SIGNING_CERTIFICATE-NOTFOUND
        CACHE PATH "Signing certificate PFX file")

    # Use proper manifest file
    if(MSVC12)
        set(MyApplication_MANIFEST ${CMAKE_SYSTEM_NAME}.MSVC2013.appxmanifest)
    elseif(MSVC14)
        set(MyApplication_MANIFEST ${CMAKE_SYSTEM_NAME}.MSVC2015.appxmanifest)
    else()
        message(FATAL_ERROR "Unsupported MSVC version")
    endif()
    set_source_files_properties(${MyApplication_MANIFEST} PROPERTIES
        VS_DEPLOYMENT_CONTENT 1)

    # Assets
    set(MyApplication_ASSETS
        ../assets/logo.png
        ../assets/logo-small.png
        ../assets/logo-store.png
        ../assets/splash.png)
    set_source_files_properties(${MyApplication_ASSETS} PROPERTIES
        VS_DEPLOYMENT_CONTENT 1
        VS_DEPLOYMENT_LOCATION "assets")

    # DLLs of dependencies
    corrade_find_dlls_for_libs(MyApplication_BINARIES
        ${OPENGLES2_LIBRARY}
        ${EGL_LIBRARY}
        ${SDL2_LIBRARY})
    set_source_files_properties(${MyApplication_BINARIES} PROPERTIES
        VS_DEPLOYMENT_CONTENT 1)

    add_executable(MyApplication WIN32 MyApplication.cpp
        ${MyApplication_MANIFEST}
        ${MyApplication_ASSETS}
        ${MyApplication_BINARIES}
        ${SIGNING_CERTIFICATE})
else()
    add_executable(MyApplication MyApplication.cpp)
endif()

target_link_libraries(MyApplication
    ${MAGNUM_APPLICATION_LIBRARIES}
    ${MAGNUM_LIBRARIES})

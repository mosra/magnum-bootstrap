find_package(Magnum REQUIRED
    Sdl2Application)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CORRADE_CXX_FLAGS}")
include_directories(${MAGNUM_INCLUDE_DIRS} ${MAGNUM_APPLICATION_INCLUDE_DIRS})

set(MACOSX_BUNDLE_GUI_IDENTIFIER "cz.mosra.magnum.MyApplication")

add_executable(MyApplication MACOSX_BUNDLE MyApplication.cpp)
target_link_libraries(MyApplication
    ${MAGNUM_APPLICATION_LIBRARIES}
    ${MAGNUM_LIBRARIES})
set_target_properties(MyApplication PROPERTIES XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "YES")

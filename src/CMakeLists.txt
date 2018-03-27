find_package(Magnum REQUIRED
    Sdl2Application)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

add_executable(MyApplication MACOSX_BUNDLE MyApplication.cpp)
target_link_libraries(MyApplication PRIVATE
    Magnum::Application
    Magnum::Magnum)
if(CORRADE_TARGET_IOS)
    set_target_properties(MyApplication PROPERTIES
        MACOSX_BUNDLE ON
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/MacOSXBundleInfo.plist.in
        XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "YES")
endif()

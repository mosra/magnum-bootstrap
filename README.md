This repository contains "bootstrap projects" for the Magnum C++11/C++14
graphics engine.

[![Build Status](https://travis-ci.org/mosra/magnum-bootstrap.svg?branch=master)](https://travis-ci.org/mosra/magnum-bootstrap)
[![Build Status](https://ci.appveyor.com/api/projects/status/90yi0xhj3pmkk1ig/branch/master?svg=true)](https://ci.appveyor.com/project/mosra/magnum-bootstrap/branch/master)
[![Join the chat at https://gitter.im/mosra/magnum](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/mosra/magnum?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

-   Project homepage — https://magnum.graphics/
-   Documentation — https://doc.magnum.graphics/
-   GitHub project page — https://github.com/mosra/magnum-bootstrap

Setting up a new project can be pretty gruesome and nobody likes repeating the
same process every time. This repository provides "bootstrap" project
structures for many use cases, helping you get up and running in no time.

USAGE
=====

To use Magnum, you obviously need to have Magnum installed. The whole building
and installation process (along with the following guide) is thoroughly
explained in Magnum documentation, particularly in the
[Getting Started Guide](https://doc.magnum.graphics/magnum/getting-started.html).

Minimal dependencies
--------------------

*   C++ compiler with good C++11 support. Compilers which are tested to have
    everything needed are **GCC** >= 4.7, **Clang** >= 3.1 and **MSVC** >= 2015.
    On Windows you can also use **MinGW-w64**.
*   **CMake** >= 2.8.12
*   **Corrade**, **Magnum** -- The engine itself

Note that each bootstrap project has additional dependency requirements, listed
below. See [Magnum building documentation](https://doc.magnum.graphics/magnum/building.html)
for more information.

Bootstrapping the project
-------------------------

Desired usage is to download selected branch from the list below as an archive
(using the Download button in GitHub) or by using URL similar to one of the
following (replace `<branch>` with desired branch name):

    https://github.com/mosra/magnum-bootstrap/archive/<branch>.tar.gz
    https://github.com/mosra/magnum-bootstrap/archive/<branch>.zip

After extracting the downloaded archive you can build and run the application
with these four commands:

    mkdir build && cd build
    cmake ..
    cmake --build .
    ./src/MyApplication # or ./src/Debug/MyApplication

For crosscompiling (in `base-nacl` and `base-emscripten` branches, see below)
you will need to have the `toolchains` submodule. It is present in Git clone
and can be updated with these commands:

    git submodule init
    git submodule update

However, because you should use downloaded archive anyway, you need to manually
download snapshot of toolchains repository from https://github.com/mosra/toolchains
and put the contents in `toolchains/` subdirectory.

Contents of the repository
--------------------------

This `master` branch contains just an README file and the actual bootstrap
projects are in various other branches, each covering some particular use case.

### Base application

The [`base`](https://github.com/mosra/magnum-bootstrap/tree/base) branch
contains barebones windowed application using `Platform::Sdl2Application` with
only the essential files. You need Magnum built with `WITH_SDL2APPLICATION`
enabled.

### Base application using GLFW

The [`base-glfw`](https://github.com/mosra/magnum-bootstrap/tree/base-glfw)
branch is similar to `base` one, except that it uses `Platform::GlfwApplication`
instead of `Platform::Sdl2Application`. You need Magnum built with
`WITH_GLFWAPPLICATION` enabled.

### Base application using GLUT

The [`base-glut`](https://github.com/mosra/magnum-bootstrap/tree/base-glut)
branch is similar to `base` one, except that it uses `Platform::GlutApplication`
instead of `Platform::Sdl2Application`. You need Magnum built with
`WITH_GLUTAPPLICATION` enabled.

### Base application using Qt

The [`base-qt`](https://github.com/mosra/magnum-bootstrap/tree/base-qt)
branch does not use any of the application wrappers provided in `Platform`
namespace, but uses Qt5 window and context creation directly and manually
initializes Magnum on top of that using EGL on embedded devices, WGL on
Windows, CGL on macOS and GLX on Unix/Linux. You need Magnum built with
`WITH_EGLCONTEXT`, `WITH_WGLCONTEXT`, `WITH_CGLCONTEXT` or `WITH_GLXCONTEXT`
enabled, depending on the platform of your choice.

### Windowless application

The [`windowless`](https://github.com/mosra/magnum-bootstrap/tree/windowless)
branch contains windowless application using `Platform::WindowlessGlxApplication`
on X11-based Unix, `Platform::WindowlessCglApplication` on macOS,
`Platform::WindowlessWglApplication` on Windows, `Platform::WindowlessWindowsEglApplication`
on Windows GLES or ANGLE, `Platform::WindowlessEglApplication` on headless
systems supporting EGL and `Platform::WindowlessIosApplication` on iOS. Useful
for querying information about the renderer, offscreen rendering, image
processing etc. You need Magnum built with `WITH_WINDOWLESS*APPLICATION`
enabled, depending on the platform of your choice.

### Scene graph

The [`scenegraph2D`](https://github.com/mosra/magnum-bootstrap/tree/scenegraph2D)
and [`scenegraph3D`](https://github.com/mosra/magnum-bootstrap/tree/scenegraph3D)
branches contain application prepared for using 2D/3D `SceneGraph`. You need
Magnum built with `WITH_SDL2APPLICATION` and `WITH_SCENEGRAPH` enabled.

### Base application with port to Emscripten

The [`base-emscripten`](https://github.com/mosra/magnum-bootstrap/tree/base-emscripten)
branch contains application using `Platform::Sdl2Application` for both desktop
and Emscripten build. You need Magnum built with `WITH_SDL2APPLICATION` enabled
and you can use the commands above to build the desktop version.

For Emscripten build you need to have Emscripten installed with Corrade and
Magnum crosscompiled for Emscripten, don't forget to build Magnum with
`WITH_SDL2APPLICATION` enabled. See
[Corrade's](https://doc.magnum.graphics/corrade/building-corrade.html#building-corrade-cross-emscripten)
and [Magnum's](https://doc.magnum.graphics/magnum/building.html#building-cross-emscripten)
building documentation for more information.

In the `toolchains/` submodule there are two toolchain files. The
`generic/Emscripten.cmake` is for the classical (asm.js) build, the
`generic/Emscripten-wasm.cmake` is for WebAssembly build. Don't forget to adapt
`EMSCRIPTEN_PREFIX` variable in `generic/Emscripten*.cmake` to path where
Emscripten is installed; you can also pass it explicitly on command-line using
`-DEMSCRIPTEN_PREFIX`. Default is `/usr/lib/emscripten`.

Then create build directory and run `cmake` and build/install commands in it.
Set `CMAKE_PREFIX_PATH` to where you have all the dependencies installed, set
`CMAKE_INSTALL_PREFIX` to have the files installed in proper location (a
webserver, e.g.  `/srv/http/emscripten`).

    mkdir build-emscripten && cd build-emscripten
    cmake .. \
        -DCMAKE_TOOLCHAIN_FILE="../toolchains/generic/Emscripten.cmake" \
        -DCMAKE_PREFIX_PATH=/usr/lib/emscripten/system \
        -DCMAKE_INSTALL_PREFIX=/srv/http/emscripten
    cmake --build .
    cmake --build . --target install

You can then open `MyApplication.html` in your browser (through webserver, e.g.
`http://localhost/emscripten/MyApplication.html`).

### Windowless application with port to Emscripten

The [`windowless-emscripten`](https://github.com/mosra/magnum-bootstrap/tree/base-emscripten)
branch contains a version of the `windowless` bootstrap project which in
addition uses `Platform::WindowlessEglApplication` for Emscripten build. You
need Magnum built with `WITH_WINDOWLESS*APPLICATION` enabled depending on your
platform of choice and you can use the commands above to build the desktop
version.

For Emscripten build you need to have Emscripten installed with Corrade and
Magnum crosscompiled for Emscripten, don't forget to build Magnum with
`WITH_WINDOWLESSEGLAPPLICATION` enabled. See
[Corrade's](https://doc.magnum.graphics/corrade/building-corrade.html#building-corrade-cross-emscripten)
and [Magnum's](https://doc.magnum.graphics/magnum/building.html#building-cross-emscripten)
building documentation for more information.

In the `toolchains/` submodule there are two toolchain files. The
`generic/Emscripten.cmake` is for the classical (asm.js) build, the
`generic/Emscripten-wasm.cmake` is for WebAssembly build. Don't forget to adapt
`EMSCRIPTEN_PREFIX` variable in `generic/Emscripten*.cmake` to path where
Emscripten is installed; you can also pass it explicitly on command-line using
`-DEMSCRIPTEN_PREFIX`. Default is `/usr/lib/emscripten`.

Then create build directory and run `cmake` and build/install commands in it.
Set `CMAKE_PREFIX_PATH` to where you have all the dependencies installed, set
`CMAKE_INSTALL_PREFIX` to have the files installed in proper location (a
webserver, e.g.  `/srv/http/emscripten`).

    mkdir build-emscripten && cd build-emscripten
    cmake .. \
        -DCMAKE_TOOLCHAIN_FILE="../toolchains/generic/Emscripten.cmake" \
        -DCMAKE_PREFIX_PATH=/usr/lib/emscripten/system \
        -DCMAKE_INSTALL_PREFIX=/srv/http/emscripten
    cmake --build .
    cmake --build . --target install

You can then open `MyApplication.html` in your browser (through webserver, e.g.
`http://localhost/emscripten/MyApplication.html`).

### Base application with port to Android

The [`base-android`](https://github.com/mosra/magnum-bootstrap/tree/base-android)
branch contains application using `Platform::Sdl2Application` for desktop build
and `Platform::AndroidApplication` for Android build. For desktop build you
need Magnum built with `WITH_SDL2APPLICATION` enabled and you can use the
commands above to build the desktop version.

For Android build you need to have Android NDK installed with Corrade and
Magnum crosscompiled for Android, Magnum built with `WITH_ANDROIDAPPLICATION`
enabled. See [Corrade's](https://doc.magnum.graphics/corrade/building-corrade.html#building-corrade-cross-android)
and [Magnum's](https://doc.magnum.graphics/magnum/building.html#building-cross-android)
building documentation for more information.

In order to build the application and install it on your device, use Gradle:

    gradle build
    gradle installDebug

### Base application with port to iOS

The [`base-ios`](https://github.com/mosra/magnum-bootstrap/tree/base-ios)
branch contains application using `Platform::Sdl2Application` for both desktop
and iOS build. You need Magnum built with `WITH_SDL2APPLICATION` enabled and
you can use the commands above to build the desktop version.

For iOS you need macOS and XCode installed with Corrade and Magnum
crosscompiled for iOS, don't forget to build Magnum with `WITH_SDL2APPLICATION`
enabled. See [Corrade's](https://doc.magnum.graphics/corrade/building-corrade.html#building-corrade-cross-ios)
and [Magnum's](https://doc.magnum.graphics/magnum/building.html#building-cross-ios)
building documentation for more information.

Then create build directory and run `cmake` to generate the Xcode project. Set
`CMAKE_OSX_ROOT` to SDK you want to target and enable all desired architectures
in `CMAKE_OSX_ARCHITECTURES`. Set `CMAKE_PREFIX_PATH` to the directory where
you have all the dependencies.

    mkdir build-ios && cd build-ios
    cmake .. \
        -DCMAKE_TOOLCHAIN_FILE=../toolchains/generic/iOS.cmake \
        -DCMAKE_OSX_SYSROOT=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk \
        -DCMAKE_OSX_ARCHITECTURES="arm64;armv7;armv7s" \
        -DCMAKE_PREFIX_PATH=~/ios-libs \
        -G Xcode

You can then open the generated project file in Xcode and build/deploy it from
there.

### Base application with port to Windows RT (Store/Phone)

The [`base-winrt`](https://github.com/mosra/magnum-bootstrap/tree/base-winrt)
branch contains application using `Platform::Sdl2Application` for both desktop
and Windows RT build. You need Magnum built with `WITH_SDL2APPLICATION` enabled
and you can use the commands above to build the desktop version.

For Windows RT build you need to have at least Windows 8.1, Visual Studio 2013
and Windows 8.1 Store/Phone SDK installed with Corrade and Magnum crosscompiled
for Windows RT, don't forget to build Magnum with `WITH_SDL2APPLICATION` enabled.
See [Corrade's](https://doc.magnum.graphics/corrade/building-corrade.html#building-corrade-cross-winrt)
and [Magnum's](https://doc.magnum.graphics/magnum/building.html#building-cross-winrt)
building documentation for more information.

You need to provide [your own `*.pfx` certificate file](https://msdn.microsoft.com/en-us/library/windows/desktop/jj835832.aspx)
and pass it to CMake in a `SIGNING_CERTIFICATE` variable. The bootstrap
application assumes that SDL2 and ANGLE is built as DLL and both Corrade and
Magnum are built statically. Assuming the native Corrade installation is in
`C:/Sys` and all WinRT dependencies are in `C:/Sys-winrt`, the build can be
done similarly to the following:

    mkdir build-winrt && cd build-winrt
    cmake .. ^
        -DCORRADE_RC_EXECUTABLE="C:/Sys/bin/corrade-rc.exe" ^
        -DCMAKE_PREFIX_PATH="C:/Sys-winrt" ^
        -DCMAKE_SYSTEM_NAME=WindowsStore ^
        -DCMAKE_SYSTEM_VERSION=8.1 ^
        -DSIGNING_CERTIFICATE=<path-to-your-pfx-file> ^
        -G "Visual Studio 14 2015"
    cmake --build .

Change `WindowsStore` to `WindowsPhone` if you want to build for Windows Phone
instead. The `build-winrt/src/AppPackages` directory will then contain the
final package along with a PowerShell script for easy local installation.

CONTACT & SUPPORT
=================

If you want to contribute to Magnum, if you spotted a bug, need a feature or
have an awesome idea, you can get a copy of the sources from GitHub and start
right away! There is the already mentioned guide about
[how to download and build Magnum](https://doc.magnum.graphics/magnum/building.html)
and also a guide about [coding style and best practices](https://doc.magnum.graphics/magnum/coding-style.html)
which you should follow to keep the library as consistent and maintainable as
possible.

-   Project homepage — https://magnum.graphics/
-   Documentation — https://doc.magnum.graphics/
-   GitHub — https://github.com/mosra/magnum-bootstrap and the
    [#magnum](https://github.com/topics/magnum) topic
-   GitLab — https://gitlab.com/mosra/magnum-bootstrap
-   Gitter community chat — https://gitter.im/mosra/magnum
-   E-mail — info@magnum.graphics
-   Google Groups mailing list — magnum-engine@googlegroups.com
    ([archive](https://groups.google.com/forum/#!forum/magnum-engine))
-   Twitter — https://twitter.com/czmosra and the
    [#MagnumEngine](https://twitter.com/hashtag/MagnumEngine) hashtag

See also the Magnum Project [Contact & Support page](https://magnum.graphics/contact/)
for further information.

LICENSE
=======

While Magnum itself and its documentation are licensed under the MIT/Expat
license, all boostrap projects are put into public domain (or UNLICENSE) to
free you from any legal obstacles when reusing the code in your apps. See the
[COPYING](COPYING) file for details.

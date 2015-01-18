This repository contains "bootstrap projects" for Magnum C++11 OpenGL graphics
engine. If you don't know what Magnum is, see https://github.com/mosra/magnum.

Setting up a new project can be pretty gruesome and nobody likes repeating the
same process every time. This repository provides "bootstrap" project
structures for many use cases, helping you get up and running in no time.

USAGE
=====

To use Magnum, you obviously need to have Magnum installed. Note that the whole
building and installation process (along with the following guide) is
thoroughly explained in Magnum documentation, particularly in the
[Getting Started Guide](http://mosra.cz/blog/magnum-doc/getting-started.html).

Minimal dependencies
--------------------

*   C++ compiler with good C++11 support. Currently there are two compilers
    which are tested to have everything needed: **GCC** >= 4.6 and **Clang**
    >= 3.1. On Windows you can use **MinGW**. GCC 4.5, 4.4 and **MSVC** 2013
    are supported if you use `compatibility` branch of Corrade and Magnum
    libraries.
*   **CMake** >= 2.8.9
*   **Corrade**, **Magnum** -- The engine itself

Note that each bootstrap project has additional dependency requirements, listed
below. See [Magnum building documentation](http://mosra.cz/blog/magnum-doc/building.html)
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

### Base application using GLUT

The [`base-glut`](https://github.com/mosra/magnum-bootstrap/tree/base-glut)
branch is similar to `base` one, except that it uses `Platform::GlutApplication`
instead of `Platform::Sdl2Application`. You need Magnum built with
`WITH_GLUTAPPLICATION` enabled.

### Windowless application

The [`windowless`](https://github.com/mosra/magnum-bootstrap/tree/windowless)
branch contains windowless application using `Platform::WindowlessGlxApplication`
on X11-based Unix, `Platform::WindowlessCglApplication` on OS X and
`Platform::WindowlessWglApplication` on Windows, other platforms are not
supported yet. Useful for querying information about the renderer, offscreen
rendering, image processing etc. You need Magnum built with
`WITH_WINDOWLESSGLXAPPLICATION`, `WITH_WINDOWLESSCGLAPPLICATION` or
`WITH_WINDOWLESSWGLAPPLICATION` enabled.

### Scene graph

The [`scenegraph2D`](https://github.com/mosra/magnum-bootstrap/tree/scenegraph2D)
and [`scenegraph3D`](https://github.com/mosra/magnum-bootstrap/tree/scenegraph3D)
branches contain application prepared for using 2D/3D `SceneGraph`. You need
Magnum built with `WITH_SDL2APPLICATION` and `WITH_SCENEGRAPH` enabled.

### Base application with port to Google Chrome Native Client

The [`base-nacl`](https://github.com/mosra/magnum-bootstrap/tree/base-nacl)
branch contains application using `Platform::Sdl2Application` for desktop build
and `Platform::NaClApplication` for NaCl build. For desktop build you need
Magnum built with `WITH_SDL2APPLICATION` enabled and you can use the commands
above to build the desktop version.

For NaCl build you need to have NaCl SDK installed with Corrade and Magnum
crosscompiled for Native Client, Magnum built with `WITH_NACLAPPLICATION`
enabled. See [Corrade's](http://mosra.cz/blog/corrade-doc/building-corrade.html#building-cross-nacl)
and [Magnum's](http://mosra.cz/blog/magnum-doc/building.html#building-cross-nacl)
building documentation for more information.

In the `toolchains/` submodule don't forget to adapt `NACL_PREFIX` variable in
`generic/NaCl-newlib-x86-32.cmake` and `generic/NaCl-newlib-x86-64.cmake` to
path where your SDK is installed. Default is `/usr/nacl`. You may need to adapt
also `NACL_TOOLCHAIN_PATH` so CMake is able to find the compiler.

Then create build directories for x86-32 and x86-64 and run `cmake` and
build/install commands in them. The toolchains need access to the platform
file, so be sure to properly set **absolute** path to `toolchains/modules/`
directory containing `Platform/NaCl.cmake`. Set `CMAKE_INSTALL_PREFIX` to
location of your webserver to have the files installed in proper location.

    mkdir build-nacl-x86-32 && cd build-nacl-x86-32
    cmake .. \
        -DCMAKE_MODULE_PATH="/absolute/path/to/toolchains/modules" \
        -DCMAKE_TOOLCHAIN_FILE="../toolchains/generic/NaCl-newlib-x86-32.cmake" \
        -DCMAKE_INSTALL_PREFIX=/srv/http/nacl
    cmake --build .
    cmake --build . --target install

    mkdir -p build-nacl-x86-64
    cd build-nacl-x86-64
    cmake .. \
        -DCMAKE_MODULE_PATH="/absolute/path/to/toolchains/modules" \
        -DCMAKE_TOOLCHAIN_FILE="../toolchains/generic/NaCl-newlib-x86-64.cmake" \
        -DCMAKE_INSTALL_PREFIX=/srv/http/nacl
    cmake --build .
    cmake --build . --target install

You can then open `MyApplication.html` through your webserver in Chrome.

### Base application with port to Emscripten (HTML5/WebGL)

The [`base-emscripten`](https://github.com/mosra/magnum-bootstrap/tree/base-emscripten)
branch contains application using `Platform::Sdl2Application` for both desktop
and Emscripten build. You need Magnum built with `WITH_SDL2APPLICATION` enabled
and you can use the commands above to build the desktop version.

For Emscripten build you need to have Emscripten installed with Corrade and
Magnum crosscompiled for Emscripten, don't forget to build Magnum with
`WITH_SDL2APPLICATION` enabled. See
[Corrade's](http://mosra.cz/blog/corrade-doc/building-corrade.html#building-cross-emscripten)
and [Magnum's](http://mosra.cz/blog/magnum-doc/building.html#building-cross-emscripten)
building documentation for more information.

In the `toolchains/` submodule don't forget to adapt `EMSCRIPTEN_PREFIX`
variable in `generic/Emscripten.cmake` to path where Emscripten is installed.
Default is `/usr/lib/emscripten`.

Then create build directory and run `cmake` and build/install commands in it.
The toolchain needs access to its platform file, so be sure to properly set
**absolute** path to `toolchains/modules/` directory containing
`Platform/Emscripten.cmake`. Set `CMAKE_INSTALL_PREFIX` to have the files
installed in proper location (e.g. a webserver).

    mkdir build-emscripten && cd build-emscripten
    cmake .. \
        -DCMAKE_MODULE_PATH="/absolute/path/to/toolchains/modules" \
        -DCMAKE_TOOLCHAIN_FILE="../toolchains/generic/Emscripten.cmake" \
        -DCMAKE_INSTALL_PREFIX=/usr/lib/emscripten/system
    cmake --build .
    cmake --build . --target install

You can then open `MyApplication.html` in Chrome or Firefox.

### Base application with port to Android

The [`base-android`](https://github.com/mosra/magnum-bootstrap/tree/base-android)
branch contains application using `Platform::Sdl2Application` for desktop build
and `Platform::AndroidApplication` for Android build. For desktop build you
need Magnum built with `WITH_ANDROIDAPPLICATION` enabled and you can use the
commands above to build the desktop version.

For Android build you need to have Android NDK installed with Corrade and
Magnum crosscompiled for Android, Magnum built with `WITH_ANDROIDAPPLICATION`
enabled. See [Corrade's](http://mosra.cz/blog/corrade-doc/building-corrade.html#building-cross-android)
and [Magnum's](http://mosra.cz/blog/magnum-doc/building.html#building-cross-android)
building documentation for more information.

In the `toolchains/` submodule don't forget to adapt `ANDROID_NDK_ROOT` in
`toolchains/generic/Android-*.cmake` to path where NDK is installed. Default is
`/opt/android-ndk`. Adapt also `ANDROID_SYSROOT` to your preferred API level.
You might also need to update `ANDROID_TOOLCHAIN_PREFIX` and
`ANDROID_TOOLCHAIN_ROOT` to fit your system.

First you need to update Android project files with the following command. It
will create `build.xml` file for Ant and a bunch of other files. You need to
specify the target for which you will build in the `-t` parameter. List of all
targets can be obtained by calling `android list target`.

    android update project -p . -t "android-19"

Then create build directories for ARM and x86 and run `cmake` and build command
in them. The toolchains need access to the platform file, so be sure to
properly set **absolute** path to `toolchains/modules/` directory containing
`Platform/Android.cmake`.

    mkdir build-android-arm && cd build-android-arm
    cmake .. \
        -DCMAKE_MODULE_PATH="/absolute/path/to/toolchains/modules" \
        -DCMAKE_TOOLCHAIN_FILE="../toolchains/generic/Android-ARM.cmake"
    cmake --build .

    mkdir build-android-x86 && cd build-android-x86
    cmake .. \
        -DCMAKE_MODULE_PATH="/absolute/path/to/toolchains/modules" \
        -DCMAKE_TOOLCHAIN_FILE="../toolchains/generic/Android-x86.cmake"
    cmake --build .

The compiled binaries will be put into `lib/armeabi-v7a` and `lib/x86`. You can
then build the APK package simply by running `ant`. The resulting APK package
can be then installed directly on the device or emulator using `adb install`.

    ant debug
    adb install bin/NativeActivity-debug.apk

CONTACT
=======

Want to learn more about the library? Found a bug or want to tell me an awesome
idea? Feel free to visit my website or contact me at:

*   Website -- http://mosra.cz/blog/magnum.php
*   GitHub -- https://github.com/mosra/magnum-bootstrap
*   IRC -- join `#magnum-engine` channel on freenode
*   Google Groups -- https://groups.google.com/forum/#!forum/magnum-engine
*   Twitter -- https://twitter.com/czmosra
*   E-mail -- mosra@centrum.cz
*   Jabber -- mosra@jabbim.cz

LICENSE
=======

While Magnum itself is released under MIT license (see [COPYING](COPYING) file
for details), the bootstrap projects are released to public domain. To keep
them as small and terse as possible no licensing information is put anywhere,
allowing the users to freely use any license without dealing with relicensing
issues.

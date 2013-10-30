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
    which are tested to support everything needed: **GCC** >= 4.6 and **Clang**
    >= 3.1. On Windows you can use **MinGW**, Visual Studio compiler still
    lacks some needed features.
*   **CMake** >= 2.8.8
*   **Corrade**, **Magnum** - The engine itself

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

    mkdir -p build && cd build
    cmake ..
    make
    ./src/MyApplication

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
contains barebones windowed application using `Platform::GlutApplication` with
only the essential files. You need Magnum built with `WITH_GLUTAPPLICATION`
enabled.

### Windowless application

The [`windowless`](https://github.com/mosra/magnum-bootstrap/tree/windowless)
branch contains windowless application using `Platform::WindowlessGlxApplication`
(Linux only). Useful for querying information about the renderer, offscreen
rendering, image processing etc. You need Magnum built with
`WITH_WINDOWLESSGLXAPPLICATION` enabled.

### Scene graph

The [`scenegraph2D`](https://github.com/mosra/magnum-bootstrap/tree/scenegraph2D)
and [`scenegraph3D`](https://github.com/mosra/magnum-bootstrap/tree/scenegraph3D)
branches contain application prepared for using 2D/3D `SceneGraph`. You need
Magnum built with `WITH_GLUTAPPLICATION` and `WITH_SCENEGRAPH` enabled.

## Base application with port to Google Native Client

The [`base-nacl`](https://github.com/mosra/magnum-bootstrap/tree/base-nacl)
branch contains application using `Platform::GlutApplication` for desktop build
and `Platform::NaClApplication` for NaCl build. For desktop build you need
Magnum built with `WITH_GLUTAPPLICATION` enabled and you can use the commands
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

Then create build directories for x86-32 and x86-64 and run `cmake` and `make`
in them. The toolchains need access to the platform file, so be sure to
properly set **absolute** path to `modules/` directory containing
`Platform/NaCl.cmake`. Set `CMAKE_INSTALL_PREFIX` to location of your webserver
to have `make install` install the files in proper location.

    mkdir -p build-nacl-x86-32
    cd build-nacl-x86-32
    cmake .. \
        -DCMAKE_MODULE_PATH="/absolute/path/to/toolchains/modules" \
        -DCMAKE_TOOLCHAIN_FILE="../toolchains/generic/NaCl-newlib-x86-32.cmake" \
        -DCMAKE_INSTALL_PREFIX=/srv/http/nacl
    make && make install

    mkdir -p build-nacl-x86-64
    cd build-nacl-x86-64
    cmake .. \
        -DCMAKE_MODULE_PATH="/absolute/path/to/toolchains/modules" \
        -DCMAKE_TOOLCHAIN_FILE="../toolchains/generic/NaCl-newlib-x86-64.cmake" \
        -DCMAKE_INSTALL_PREFIX=/srv/http/nacl
    make && make install

You can then open `MyApplication.html` through your webserver in Chrome.

## Base application with port to Emscripten

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
Default is `/usr/emscripten`.

Then create build directory and run `cmake` and `make` in it. The toolchain
needs access to its platform file, so be sure to properly set **absolute** path
to `modules/` directory containing `Platform/Emscripten.cmake`. Set
`CMAKE_INSTALL_PREFIX` to have `make install` install the files in proper
location (e.g. a webserver).

    mkdir -p build-emscripten
    cd build-emscripten
    cmake .. \
        -DCMAKE_MODULE_PATH="/absolute/path/to/toolchains/modules" \
        -DCMAKE_TOOLCHAIN_FILE="../toolchains/generic/Emscripten.cmake"
        -DCMAKE_INSTALL_PREFIX=/srv/http/nacl
    make && make install

You can then open `MyApplication.html` in Chrome or Firefox.

CONTACT
=======

Want to learn more about the library? Found a bug or want to tell me an awesome
idea? Feel free to visit my website or contact me at:

*   Website - http://mosra.cz/blog/magnum.php
*   GitHub - https://github.com/mosra/magnum-bootstrap
*   Twitter - https://twitter.com/czmosra
*   E-mail - mosra@centrum.cz
*   Jabber - mosra@jabbim.cz

LICENSE
=======

While Magnum itself is released under MIT license (see [COPYING](COPYING) file
for details), the bootstrap projects are released to public domain. To keep
them as small and terse as possible no licensing information is put anywhere,
allowing the users to freely use any license without dealing with relicensing
issues.

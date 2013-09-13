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
*   **Magnum** - The engine itself

Bootstrapping the project
-------------------------

This `master` branch contains just an README file and the actual bootstrap
projects are in various other branches, each covering some particular use case:

*   `base` -- Base for all projects with only the essential files
*   `scenegraph2D` -- Base for applications using 2D scene graph
*   `scenegraph3D` -- Base for applications using 3D scene graph
*   `windowless` -- Windowless application, usable for querying information
    about the renderer, offscreen rendering, image processing etc.

Desired usage is to download given branch as an archive (using the Download
button in GitHub) or by using URL similar to one of the following (replace the
`(branch)` with desired branch name):

    https://github.com/mosra/magnum-bootstrap/archive/(branch).tar.gz
    https://github.com/mosra/magnum-bootstrap/archive/(branch).zip

After extracting the downloaded archive you can build and run the application
with these four commands:

    mkdir -p build && cd build
    cmake ..
    make
    ./src/MyApplication

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

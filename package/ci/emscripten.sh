#!/bin/bash
set -ev

git clone --depth 1 git://github.com/mosra/corrade.git
cd corrade
git submodule update --init

# Build native corrade-rc
mkdir build && cd build || exit /b
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=$HOME/deps-native \
    -DCMAKE_INSTALL_RPATH=$HOME/deps-native/lib \
    -DWITH_INTERCONNECT=OFF \
    -DWITH_PLUGINMANAGER=OFF \
    -DWITH_TESTSUITE=OFF \
    -DBUILD_DEPRECATED=OFF \
    -G Ninja
ninja install
cd ..

# Crosscompile Corrade
mkdir build-emscripten && cd build-emscripten
cmake .. \
    -DCORRADE_RC_EXECUTABLE=$HOME/deps-native/bin/corrade-rc \
    -DCMAKE_TOOLCHAIN_FILE=../toolchains/generic/Emscripten.cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_CXX_FLAGS_RELEASE="-DNDEBUG -O1" \
    -DCMAKE_EXE_LINKER_FLAGS_RELEASE="-O1" \
    -DCMAKE_INSTALL_PREFIX=$HOME/deps \
    -DWITH_INTERCONNECT=OFF \
    -DWITH_PLUGINMANAGER=OFF \
    -DWITH_TESTSUITE=OFF \
    -DBUILD_DEPRECATED=OFF \
    -G Ninja
ninja install
cd ../..

# Crosscompile Magnum
git clone --depth 1 git://github.com/mosra/magnum.git
cd magnum
git submodule update --init
mkdir build-emscripten && cd build-emscripten
cmake .. \
    -DCORRADE_RC_EXECUTABLE=$HOME/deps-native/bin/corrade-rc \
    -DCMAKE_TOOLCHAIN_FILE=../toolchains/generic/Emscripten.cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_CXX_FLAGS_RELEASE="-DNDEBUG -O1" \
    -DCMAKE_EXE_LINKER_FLAGS_RELEASE="-O1" \
    -DCMAKE_INSTALL_PREFIX=$HOME/deps \
    -DCMAKE_FIND_ROOT_PATH=$HOME/deps \
    -DWITH_AUDIO=OFF \
    -DWITH_DEBUGTOOLS=OFF \
    -DWITH_MESHTOOLS=OFF \
    -DWITH_PRIMITIVES=OFF \
    -DWITH_SCENEGRAPH=OFF \
    -DWITH_SHADERS=OFF \
    -DWITH_SHADERTOOLS=OFF \
    -DWITH_TEXT=OFF \
    -DWITH_TEXTURETOOLS=OFF \
    -DWITH_TRADE=OFF \
    -DWITH_EMSCRIPTENAPPLICATION=ON \
    -DWITH_WINDOWLESSEGLAPPLICATION=ON \
    -DTARGET_GLES2=$TARGET_GLES2 \
    -DBUILD_DEPRECATED=OFF \
    -G Ninja
ninja install
cd ../..

# Crosscompile bootstrap project
git clone --depth 1 --branch $BRANCH git://github.com/mosra/magnum-bootstrap.git
cd magnum-bootstrap
git submodule update --init
mkdir build-emscripten && cd build-emscripten
cmake .. \
    -DCORRADE_RC_EXECUTABLE=$HOME/deps-native/bin/corrade-rc \
    -DCMAKE_TOOLCHAIN_FILE=../toolchains/generic/Emscripten.cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_CXX_FLAGS_RELEASE="-DNDEBUG -O1" \
    -DCMAKE_EXE_LINKER_FLAGS_RELEASE="-O1" \
    -DCMAKE_INSTALL_PREFIX=$HOME/deps \
    -DCMAKE_FIND_ROOT_PATH=$HOME/deps \
    -G Ninja
ninja

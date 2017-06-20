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
    -DBUILD_DEPRECATED=OFF
make -j install
cd ..

# Crosscompile Corrade
mkdir build-android-arm && cd build-android-arm
ANDROID_NDK=$TRAVIS_BUILD_DIR/android-ndk-r10e cmake .. \
    -DCMAKE_TOOLCHAIN_FILE=../toolchains/generic/Android-ARM.cmake \
    -DCORRADE_RC_EXECUTABLE=$HOME/deps-native/bin/corrade-rc \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=$HOME/deps \
    -DWITH_INTERCONNECT=OFF \
    -DWITH_TESTSUITE=OFF \
    -DBUILD_DEPRECATED=OFF
make -j install
cd ../..

# Crosscompile Magnum
git clone --depth 1 git://github.com/mosra/magnum.git
cd magnum
git submodule update --init
mkdir build-android-arm && cd build-android-arm
ANDROID_NDK=$TRAVIS_BUILD_DIR/android-ndk-r10e cmake .. \
    -DCMAKE_TOOLCHAIN_FILE=../toolchains/generic/Android-ARM.cmake \
    -DCORRADE_RC_EXECUTABLE=$HOME/deps-native/bin/corrade-rc \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=$HOME/deps \
    -DCMAKE_FIND_ROOT_PATH=$HOME/deps \
    -DWITH_AUDIO=OFF \
    -DWITH_DEBUGTOOLS=OFF \
    -DWITH_MESHTOOLS=OFF \
    -DWITH_PRIMITIVES=OFF \
    -DWITH_SCENEGRAPH=OFF \
    -DWITH_SHADERS=OFF \
    -DWITH_SHAPES=OFF \
    -DWITH_TEXT=OFF \
    -DWITH_TEXTURETOOLS=OFF \
    -DWITH_ANDROIDAPPLICATION=ON \
    -DTARGET_GLES2=$TARGET_GLES2 \
    -DBUILD_DEPRECATED=OFF
make -j install
cd ../..

# Crosscompile bootstrap project
git clone --depth 1 --branch $BRANCH git://github.com/mosra/magnum-bootstrap.git
cd magnum-bootstrap
git submodule update --init

android update project -p . -t "android-19"

mkdir build-android-arm && cd build-android-arm
ANDROID_NDK=$TRAVIS_BUILD_DIR/android-ndk-r10e cmake .. \
    -DCMAKE_TOOLCHAIN_FILE=../toolchains/generic/Android-ARM.cmake \
    -DCORRADE_RC_EXECUTABLE=$HOME/deps-native/bin/corrade-rc \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=$HOME/deps \
    -DCMAKE_FIND_ROOT_PATH=$HOME/deps
make -j
cd ..

ant debug

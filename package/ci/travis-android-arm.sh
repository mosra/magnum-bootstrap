#!/bin/bash
set -ev

git clone --depth 1 git://github.com/mosra/corrade.git
cd corrade

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
cmake .. \
    -DCMAKE_ANDROID_NDK=$TRAVIS_BUILD_DIR/android-ndk-r16b \
    -DCMAKE_SYSTEM_NAME=Android \
    -DCMAKE_SYSTEM_VERSION=22 \
    -DCMAKE_ANDROID_ARCH_ABI=arm64-v8a \
    -DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang \
    -DCMAKE_ANDROID_STL_TYPE=c++_static \
    -DCMAKE_BUILD_TYPE=Release \
    -DCORRADE_RC_EXECUTABLE=$HOME/deps-native/bin/corrade-rc \
    -DCMAKE_INSTALL_PREFIX=$TRAVIS_BUILD_DIR/android-ndk-r16b/platforms/android-22/arch-arm64/usr \
    -DCORRADE_INCLUDE_INSTALL_PREFIX=$TRAVIS_BUILD_DIR/android-ndk-r16b/sysroot/usr \
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
cmake .. \
    -DCMAKE_ANDROID_NDK=$TRAVIS_BUILD_DIR/android-ndk-r16b \
    -DCMAKE_SYSTEM_NAME=Android \
    -DCMAKE_SYSTEM_VERSION=22 \
    -DCMAKE_ANDROID_ARCH_ABI=arm64-v8a \
    -DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang \
    -DCMAKE_ANDROID_STL_TYPE=c++_static \
    -DCORRADE_RC_EXECUTABLE=$HOME/deps-native/bin/corrade-rc \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=$TRAVIS_BUILD_DIR/android-ndk-r16b/platforms/android-22/arch-arm64/usr \
    -DMAGNUM_INCLUDE_INSTALL_PREFIX=$TRAVIS_BUILD_DIR/android-ndk-r16b/sysroot/usr \
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

export ANDROID_NDK_HOME=$TRAVIS_BUILD_DIR/android-ndk-r16b
export CMAKE_PREFIX_PATH=$HOME/deps-native/
gradle build

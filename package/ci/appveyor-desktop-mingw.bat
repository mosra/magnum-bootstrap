rem Workaround for CMake not wanting sh.exe on PATH for MinGW. AARGH.
set PATH=%PATH:C:\Program Files\Git\usr\bin;=%
set PATH=C:\mingw-w64\x86_64-7.2.0-posix-seh-rt_v5-rev1\mingw64\bin;%APPVEYOR_BUILD_FOLDER%\deps\bin;%PATH%

rem Build Corrade
git clone --depth 1 git://github.com/mosra/corrade.git || exit /b
cd corrade || exit /b
mkdir build && cd build || exit /b
cmake .. ^
    -DCMAKE_BUILD_TYPE=Release ^
    -DCMAKE_INSTALL_PREFIX=%APPVEYOR_BUILD_FOLDER%/deps ^
    -DWITH_INTERCONNECT=OFF ^
    -DWITH_TESTSUITE=OFF ^
    -DBUILD_DEPRECATED=OFF ^
    -G Ninja || exit /b
cmake --build . || exit /b
cmake --build . --target install || exit /b
cd .. && cd ..

rem Build Magnum
git clone --depth 1 git://github.com/mosra/magnum.git || exit /b
cd magnum || exit /b
mkdir build && cd build || exit /b
cmake .. ^
    -DCMAKE_BUILD_TYPE=Release ^
    -DCMAKE_INSTALL_PREFIX=%APPVEYOR_BUILD_FOLDER%/deps ^
    -DCMAKE_PREFIX_PATH=%APPVEYOR_BUILD_FOLDER%/SDL ^
    -DWITH_AUDIO=OFF ^
    -DWITH_DEBUGTOOLS=OFF ^
    -DWITH_MESHTOOLS=OFF ^
    -DWITH_PRIMITIVES=OFF ^
    -DWITH_SCENEGRAPH=OFF ^
    -DWITH_SHADERS=OFF ^
    -DWITH_SHAPES=OFF ^
    -DWITH_TEXT=OFF ^
    -DWITH_TEXTURETOOLS=OFF %EXTRA% ^
    -DBUILD_DEPRECATED=OFF ^
    -G Ninja || exit /b
cmake --build . || exit /b
cmake --build . --target install || exit /b
cd .. && cd ..

rem Build bootstrap project
git clone --depth 1 --branch %BRANCH% git://github.com/mosra/magnum-bootstrap.git
cd magnum-bootstrap
mkdir build && cd build || exit /b
cmake .. ^
    -DCMAKE_PREFIX_PATH="%APPVEYOR_BUILD_FOLDER%/SDL" ^
    -DCMAKE_INSTALL_PREFIX=%APPVEYOR_BUILD_FOLDER%/deps ^
    -DCMAKE_BUILD_TYPE=Release ^
    -G Ninja || exit /b
cmake --build . || exit /b

export PATH=/d/apps/cmake-3.28.1-windows-x86_64/cmake-3.28.1-windows-x86_64/bin:/d/apps/qt/qt6/Tools/mingw810_64/bin:$PATH

cd /d/workspace/AppBase/3rd/yaml-cpp/0.8.0
rm -rf build
mkdir build
cd build
export PATH=/d/apps/qt/qt6/Tools/CMake_64/bin:/d/apps/qt/qt6/Tools/mingw810_64/bin:$PATH
cmake -G "Visual Studio 17 2022" ..
#cmake -G "MinGW Makefiles" ..
#mingw32-make.exe

@echo off
IF NOT EXIST build_vs2017_x64 mkdir build_vs2017_x64
pushd build_vs2017_x64
cmake -G "Visual Studio 15 Win64" -T v141,host=x64 ..
popd
@echo off

set scriptpath=%~dp0

pushd ..
cls

echo === Micro Lua Setup ===

IF EXIST "MicroLua\Micro Solution.sln" del /f "MicroLua\Micro Solution.sln"
IF EXIST MicroLua\MicroLua.vcxproj del /f MicroLua\MicroLua.vcxproj
IF EXIST MicroLua\MicroLua.vcxproj.filters del /f MicroLua\MicroLua.vcxproj.filters
IF EXIST MicroLua\MicroLua.vcxproj.user del /f MicroLua\MicroLua.vcxproj.user
IF EXIST MicroLua\bin rmdir /q /s MicroLua\bin
IF EXIST MicroLua\bin-int rmdir /q /s MicroLua\bin-int
IF EXIST MicroLua\Solution\ rmdir /q /s MicroLua\Solution\

MicroLua\Build\Premake\Windows\premake5.exe --file=MicroLua\Build\Build.lua vs2022

popd

pause

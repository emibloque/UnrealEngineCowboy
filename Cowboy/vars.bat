@echo off

call %~dp0\editor_vars.bat
set PROJECT=Cowboy

set ROOTDIR=%~dp0
set ROOTDIR=%ROOTDIR:~0,-1%

set UPROJECT=%ROOTDIR%\%PROJECT%.uproject

set UNREAL_EDITOR_EXE=%UNREAL_EDITOR_DIR%\Engine\Binaries\Win64\UnrealEditor.exe
set BUILD_BAT=%UNREAL_EDITOR_DIR%\Engine\Build\BatchFiles\Build.bat
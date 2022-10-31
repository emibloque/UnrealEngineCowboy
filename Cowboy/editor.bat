@echo off

call %~dp0\vars.bat

start "" "%UNREAL_EDITOR_EXE%" "%UPROJECT%" %*
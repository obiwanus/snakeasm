@echo off

call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64
set path=C:\Users\Ivan-Zenbook-Pro\Projects\snakeasm;%path%
doskey ci=git commit -a -m


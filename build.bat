@echo off

set CommonCompilerFlags= -DLL -MTd -nologo -Gm- -GR- -EHa- -Od -Oi -WX -W4 -wd4127 -wd4201 -wd4100 -wd4189 -wd4505 -wd4706 -FC -Z7 -Fm /I C:\libraries\include
set CommonLinkerFlags= winmm.lib user32.lib gdi32.lib opengl32.lib SDL2.lib /LIBPATH:C:\libraries\lib

if not defined DevEnvDir (
    call shell.bat
)

IF NOT EXIST build mkdir build
pushd build

@del /Q *.pdb > NUL 2> NUL
@del /Q *.gmi > NUL 2> NUL

REM 64-bit build

cl %CommonCompilerFlags% ..\c\main.cc /link %CommonLinkerFlags%

popd

@echo off
title Compile Dynamic Link Library
cls

set LibraryName=sin-directory

echo "Compiling Dynamic Link Library..."

windres "resources\resources.rc" -O coff -o "resources\resources.res"

g++ "main.cpp" -static-libgcc -static-libstdc++ -O3 -DNDEBUG -s -shared -D UNICODE -D _UNICODE -o "%LibraryName%.dll" "resources\resources.res"

pause
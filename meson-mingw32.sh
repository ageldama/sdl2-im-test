#!/bin/sh

# sudo dnf in mingw32-SDL2-static.noarch mingw32-gcc.x86_64 mingw32-gcc-c++.x86_64

meson setup --cross-file i686-w64-mingw32.txt build-mingw

#!/bin/bash
g++ sin.cpp -I/usr/include/lua5.2/ -c -fPIC
g++ -shared -Wl,--whole-archive -o sin.so sin.o -lluabind -Wl,--no-whole-archive
lua test.lua

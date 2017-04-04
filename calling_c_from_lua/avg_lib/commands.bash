#!/bin/bash
g++ luaavg.cpp -I/usr/include/lua5.2/ -c -fPIC
g++ -shared -Wl,--whole-archive -o luaavg.so luaavg.o -lluabind -Wl,--no-whole-archive
lua test.lua

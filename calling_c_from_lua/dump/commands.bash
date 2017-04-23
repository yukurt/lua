#!/bin/bash
g++ c.cpp -I/usr/include/lua5.2/ -c -fPIC
g++ -shared -Wl,--whole-archive -o c.so c.o -lluabind -Wl,--no-whole-archive
lua test.lua

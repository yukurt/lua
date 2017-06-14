#!/bin/bash

swig -lua example.i
gcc -fPIC -I/usr/include/lua5.2 -c example_wrap.c -o example_wrap.o
gcc -fPIC -I. -c example.c -o example.o
gcc -shared -I/usr/include/lua5.2 example_wrap.o example.o -o example.so
lua test.lua

#!/bin/bash

swig -lua -c++ example.i
g++ -fPIC -I/usr/include/lua5.2 -c example_wrap.cxx -o example_wrap.o
g++ -fPIC -I. -c example.cpp -o example.o
g++ -shared -I/usr/include/lua5.2 example_wrap.o example.o -o example.so
lua test.lua

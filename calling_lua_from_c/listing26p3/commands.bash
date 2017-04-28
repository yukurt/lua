#!/bin/bash

g++ c.cpp -I/usr/include/lua5.2 -L/usr/lib/x86_64-linux-gnu -llua5.2
./a.out

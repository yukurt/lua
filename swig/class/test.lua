#!/usr/bin/lua
package.loadlib('./example.so', 'luaopen_example')()

A = example.MyClass(6, 7)
A:greet()

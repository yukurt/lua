#!/usr/bin/lua
package.loadlib('./example.so', 'luaopen_example')()

A = example.Point()
A.x = 101
A.y = 202
print(A.x)
print(A.y)
A:greet()
print(swig_type(A.x))
print(swig_type(A.y))
print(swig_type(A.greet))

m = getmetatable(A)
print('/***** struct metatable *****/')
for k, v in pairs(m) do
    print(k, v)
end

g = m['.get']
print('/***** struct fields *****/')
for k, v in pairs(g) do
    print(k, v)
end

fn = m['.fn']
print('/***** struct methods *****/')
for k, v in pairs(fn) do
    print(k, v)
end

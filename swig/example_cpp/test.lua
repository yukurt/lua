package.loadlib('./example.so', 'luaopen_example')()

print(example.My_variable)
print(example.fact(5))
print(example.my_mod(5, 3))
print(example.get_time())

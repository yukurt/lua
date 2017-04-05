package.loadlib('./sin.so', 'init')()

local result = mysin(1.0)
print("result is ", result)



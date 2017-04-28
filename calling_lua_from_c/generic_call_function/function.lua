function f(x, y)
	 return (x^2 * math.sin(y)) / (1 - x)
end

function greet(greeting, name)
	 print(greeting .. ", " .. name)
	 return string.len(greeting), string.len(name)
end
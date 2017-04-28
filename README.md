# Collection of Lua examples

* calling_c_from_lua
  * interpreter
    * a simple standalone Lua interpreter
    * adapted from Ierusalimschy in Listing 25.1 of "Programming in Lua" (3rd edition)
  * avg - example of Lua calling a C++ function
  * avg_lib - same example as avg but the C++ function is saved as a library which is loaded by the Lua script
  * sin
    * example of C function saved as a library which is loaded by the Lua script
    * uses style mentioned by Ierusalimschy in chapter 27.1 of "Programming in Lua" (3rd edition)
  * dump
    * example of printing the arguments of a C function called from Lua
    * adapted from Ierusalimschy in Listing 25.2 of "Programming in Lua" (3rd edition)
  * play_stack
    * example of manipulating the stack that is used for communication between C and Lua
    * adapted from Ierusalimschy in Listing 25.3 of "Programming in Lua" (3rd edition)
  * exercise25p2
    * demonstration of Exercise 25.2 of "Programming in Lua" (3rd edition)
    * the exercise asks what the stack will look like after a series of stack operations
* calling_lua_from_c
  * listing26p1
    * example of reading a Lua file from C
	* adapted from Ierusalimschy in Listing 26.1 of "Programming in Lua" (3rd edition)
  * listing26p2
    * example of reading a table from a Lua file from C
	* this example uses lua_gettable()
	* adapted from Ierusalimschy in Listing 26.2 of "Programming in Lua" (3rd edition)
  * color_names
    * example of exporting a C table (struct array) to Lua
	* this example uses lua_settable()
	* adapted from Ierusalimschy in Chapter 26.2 of "Programming in Lua" (3rd edition)
  * listing26p3
    * example of reading a table from a Lua file from C, and referring to a struct array in C from Lua
	* this example uses lua_getfield()
	* adapted from Ierusalimschy in Listing 26.3 of "Programming in Lua" (3rd edition)
  * listing26p4
    * example of calling a Lua function from C using lua_pcall()
	* adapted from Ierusalimschy in Listing 26.4 of "Programming in Lua" (3rd edition)
  * generic_call_function
    * example of using a generic function to call any Lua function from C
	* adapted from Ierusalimschy in Chapter 26.4 of "Programming in Lua" (3rd edition)

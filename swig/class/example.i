%module example
%{
/* Includes the header in the wrapper code */
#include "example.hpp"
%}

/* Parse the header file to generate wrappers */
%include "example.hpp"

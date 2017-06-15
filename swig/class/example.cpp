#include <example.hpp>
#include <ctime>
#include <cstdio>

MyClass::MyClass(int a, int b): x(a), y(b) {}

void MyClass::greet()
{
    printf("Hello, world: x=%d y=%d\n", x, y);
}

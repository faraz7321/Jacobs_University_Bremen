#include <stdlib.h>
#include <stdio.h>

static int foo(int a)
{
    static int b = 5;
    int c;
    c = a * b;
    b += b;
    return c;
}
int main(int argc, char *argv[])
{
    return foo(foo(1));
}
// What is returned by main()?
// Which memory segments store the variables?

/*
In the example, b is stored in the initialized data segment (since it is static), a and c are stored in the
stack frame of a foo() function call, argc and argv are stored in the stack frame of the main() function
call.
*/
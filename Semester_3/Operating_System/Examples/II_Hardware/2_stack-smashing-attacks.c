#include <string.h>
static void foo(char *bar)
{
    char c[12];
    strcpy(c, bar); // no bounds checking
}
int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
        foo(argv[i]);
    return 0;
}
// Overwriting a function return address on the stack
// Returning into a ’landing area’ (typically sequences of NOPs)
// Landing area is followed by shell code (code to start a shell)
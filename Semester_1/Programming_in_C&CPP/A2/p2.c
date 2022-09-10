/*
CH-230-A
a2_p2.[c or cpp or h]
Faraz Ahmad
fahmad@jacobs.university.de
*/
#include <stdio.h>
int main()
{
    char input;
    input = getchar();
    getchar(); //ignoring ENTER
    printf("character=%c\n", input);
    printf("decimal=%d\n", input);
    printf("octal=%o\n", input);
    printf("hexadecimal=%x\n", input);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int factorial(int n)
{
    int val;
    if ((n == 0) || (n == 1))
    {
        printf("called with par = %d\n", n);
        return 1;
    }
    else
    {
        printf("called with par = %d\n", n);
        val = n * factorial(n - 1);
        printf("returning %d\n", val);
        return val;
    }
}
int main()
{
    printf("%d\n", factorial(4));
    return 0;
}

// factorial(4)
// val = 4 *factorial(3) = 24
// val = 3 * factorial(2) = 6
// val = 2 * factorial(1) = 2

/*
called with par = 4
called with par = 3
called with par = 2
called with par = 1
returning 2
returning 6
returning 24
24
*/

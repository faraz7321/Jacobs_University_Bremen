#include <iostream>
#include "yoyo.h"
//#include <sys/wait.h>
//#include <unistd.h>
static void action(int m, int n)
{
    printf("(%d,%d)\n", m, n);
    if (n > 0)
    {
        if (fork() == 0)
        {
            action(m, n - 1);
            exit(0);
        }
    }

}

int main(int argc, char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
        int a = atoi(argv[i]);
        action(a, a);
    }
    return 0;
}

/*
 * Faraz Ahmad
 * fa.ahmad@jacobs-university.de
 * CO-562 Operating Systems
 * a2_p1.c
*/

#include <stdio.h>
#include <unistd.h>

static int x = 0;

int main(int argc, char *argv[])
{
    pid_t p = getpid();

    x++;
    fork();//return 0 if child
    if (!fork())
    {
        if (fork())
        {
            x++;
        }
        x++;
    }

    printf("p%d: x = %d\n", getpid() - p, x);
    return 0;
}
/*
p0: x = 1
p1: x = 1
p4: x = 2
p5: x = 2
p2: x = 3
p3: x = 3
*/
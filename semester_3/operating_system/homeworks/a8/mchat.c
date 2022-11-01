#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    int opt;

    while ((opt = getopt(argc, argv, "zc")) != -1)
    {
        switch (opt)
        {
        case 'z':
            break;
        case 'c':
            break;
        case '?':
            printf("unknown option: %c\n", optopt);
            break;
        }
    }

    return 0;
}
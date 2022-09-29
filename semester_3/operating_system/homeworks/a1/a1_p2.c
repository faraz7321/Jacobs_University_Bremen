#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *strdup(const char *s)
{
    char *p = NULL;
    size_t len;
    if (s)
    {
        len = strlen(s);
        p = malloc(len + 1);
        if (p)
        {
            strcpy(p, s);
        }
    }
    return p;
}

int main()
{
    static char m[] = "Hello World!";
    char *p = strdup(m);
    if (!p)
    {
        perror("strdup");
        return EXIT_FAILURE;
    }
    if (puts(p) == EOF)
    {
        perror("puts");
        return EXIT_FAILURE;
    }
    if (fflush(stdout) == EOF)
    {
        perror("fflush");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
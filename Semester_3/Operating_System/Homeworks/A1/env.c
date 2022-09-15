#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

extern char **__environ;

int main(int argc, char *argv[])
{
    int opt;

    //execvp();
    getopt(argc,argv,opt);
}
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "quiz.h"

#define MAX_LENGTH 1024
char *fetch(char *url)
{
    pid_t id;
    int fd[2];
    char *buffer = (char *)malloc(MAX_LENGTH);

    // create unidirectional pipe
    if (pipe(fd) < 0)
    {
        perror("pipe();");
        exit(EXIT_FAILURE);
    }

    id = fork();

    if (id < 0)
    {
        perror("fork();");
        exit(EXIT_FAILURE);
    }
    else if (id == 0)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        execlp("curl", "curl", "-s", url, NULL);
        perror("exec");
        exit(EXIT_FAILURE);
    }
    else
    {
        close(fd[1]);
        read(fd[0], buffer, 2000);
        close(fd[0]);
    }

    return buffer;
}
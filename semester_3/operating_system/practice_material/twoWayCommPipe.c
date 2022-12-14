#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    // 5 => 5^2 = 20 => 20
    int pfd[2]; // Parent => Child
    int cfd[2]; // Child => Parent
    int rc = 0;
    pid_t pid;
    rc = pipe(pfd); // opening pipe on parent process
    if (rc == -1)
    {
        return EXIT_FAILURE;
    }
    rc = pipe(cfd); // opening pipe on child process
    if (rc == -1)
    {
        return EXIT_FAILURE;
    }
    pid = fork(); // creating child process
    if (pid == 0)
    {
        // child process
        close(pfd[1]); // close parent write fd
        close(cfd[0]); // close child read fd
        int x;
        rc = read(pfd[0], &x, sizeof(x)); // reading from parent
        if (rc == -1)
        {
            return EXIT_FAILURE;
        }
        // squaring a number and writing back to parent
        x = x * x;
        rc = write(cfd[1], &x, sizeof(x)); // writing to parent
        if (rc == -1)
        {
            return EXIT_FAILURE;
        }
        close(pfd[0]); // close parent read fd
        close(cfd[1]); // close child write fd
    }
    else
    {
        // parent process
        close(pfd[0]); // close parent read fd
        close(cfd[1]); // close child write fd
        int y = 5;
        rc = write(pfd[1], &y, sizeof(y)); // writing to parent fd
        if (rc == -1)
        {
            return EXIT_FAILURE;
        }
        rc = read(cfd[0], &y, sizeof(y)); // reading from child fd
        if (rc == -1)
        {
            return EXIT_FAILURE;
        }
        printf("Result %d\n", y);
        close(pfd[1]); // close parent write fd
        close(cfd[0]); // close child read fd
    }
}

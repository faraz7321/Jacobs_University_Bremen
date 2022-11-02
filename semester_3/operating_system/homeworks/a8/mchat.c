/*
 * Faraz Ahmad
 * fa.ahmad@jacobs-university.de
 * CO-562 Operating Systems
 * mchat.c
 */

#define _POSIX_C_SOURCE 200809L

#define _DEFAULT_SOURCE
#define _DARWIN_C_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define MEMMAP_L_FLAG 0x1
#define MEMMAP_V_FLAG 0x2

#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS MAP_ANON
#endif

#define SHM_SIZE 1024 /* 1K shared memory segment */

int main(int argc, char *argv[])
{
    key_t key;
    int shmid;
    char *data;
    int mode;
    char *A = malloc(SHM_SIZE);
    int opt;
    int count = 0;
    int i = 0;
    while ((opt = getopt(argc, argv, "zc:")) > 0)
        switch (opt)
        {
        case '?':
            puts("Bad argument");
            exit(0);
        case 'z':
            // clear msgs

            // write to file
            if (argc > 2)
            {
                for (int i = 2; i < argc; i++)
                {
                    strcat(A, argv[i]);
                    if (i == argc - 1)
                    {
                        strcat(A, "\n");
                    }
                    else
                    {
                        strcat(A, " ");
                    }
                }
            }

            break;
        case 'c':
            break;
        default:
            exit(0);
        }
    if (A != NULL)
    {
        printf("%s\n", A);
    }

    // key = ftok("/tmp/mchat.ctrl", 'R');

    // shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT);
    // if (shmid == -1)
    // {
    //     perror("shmget");
    //     exit(1);
    // }
    // data = shmat(shmid, NULL, 0);

    // if (argc == 2)
    // {
    //     printf("[%d]: \"%s\n", shmid, argv[1]);
    //     strncpy(data, argv[1], SHM_SIZE);
    // }
    // else
    //     printf("[%d]: %s\n", shmid, data);

    // /* detach from the segment: */
    // if (shmdt(data) == -1)
    // {
    //     perror("shmdt");
    //     exit(1);
    // }

    return 0;
}
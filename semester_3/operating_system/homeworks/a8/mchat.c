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
#include <stdbool.h>
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
    bool flag = false;
    int shmid, mode, opt, count = 0, i = 0;
    char *data, *A = malloc(SHM_SIZE);
    const char *ctrlFileName = "/tmp/mchat.ctrl";
    char *fileName;

    // getopt
    while ((opt = getopt(argc, argv, "zc:")) > 0)
    {
        switch (opt)
        {
        case '?':
            puts("Bad argument");
            exit(0);
        case 'z':
            flag = true;
            // write to file

            break;
        case 'c':
            fileName = malloc(strlen(optarg));
            strncpy(fileName, optarg, strlen(optarg));
            break;
        default:
            exit(0);
        }
    }

    if (argc > 2)
    {
        fprintf(stderr, "usage: shmdemo [data_to_write]\n");
        exit(1);
    }

    /* make the key: */
    if ((key = ftok(ctrlFileName, 'R')) == -1) /*Here the file must exist */
    {
        perror("ftok");
        exit(1);
    }

    /*  create the segment: */
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1)
    {
        perror("shmget");
        exit(1);
    }

    /* attach to the segment to get a pointer to it: */
    if ((data = shmat(shmid, NULL, 0)) == (void *)-1)
    {
        perror("shmat");
        exit(1);
    }

    /* read or modify the segment, based on the command line: */
    int x;
    if (argc == 2)
    {
        snprintf(data, SHM_SIZE, "[%d]: %s\n", getpid(), argv[1]);
    }
    else
        printf("%s", data);

    /* detach from the segment: */
    if (shmdt(data) == -1)
    {
        perror("shmdt");
        exit(1);
    }

    return 0;
}
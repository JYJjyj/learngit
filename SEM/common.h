#pragma once
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>


#define PATH_NAME "." 
#define PROJ_ID 1

union semun 
{
    int val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                (Linux-specific) */
};

int CreateSem(int n);

int GetSem();

int DestroySem(int semid);

int SetSemValue(int semid, int index, int value);

int GetSemValue(int semid, int index, int *value);

int P(int semid, int index);

int V(int semid, int index);

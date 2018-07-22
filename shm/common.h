#pragma once

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define PATHNAME "."
#define PROJ_ID 0x1

int CreateShm(size_t size);

int GetShm();

int DestroyShm(int shmid);




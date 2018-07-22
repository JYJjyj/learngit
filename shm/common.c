#include "common.h"

int CommonShm(size_t size, int flags)
{
    key_t key = ftok(PATHNAME, PROJ_ID); 
    if(key < 0)
    {
        perror("ftok");
        return -1;
    }

    int shmid = shmget(key, size, flags);
    if(shmid < 0)
    {
        perror("shmget");
        return -1;
    }
    return shmid;
}

int CreateShm(size_t size)
{
    return CommonShm(size, IPC_CREAT | IPC_EXCL | 0666);
}

int GetShm()
{
    return CommonShm(0,IPC_CREAT);
}


int DestroyShm(int shmid)
{
    int ret = shmctl(shmid, IPC_RMID, NULL);
    if(ret < 0)
    {
        perror("shmctl");
        return -1;
    }
    return 0;
}

int SendShm();

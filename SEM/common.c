#include "common.h"

//n为信号集中信号量的个数
int CommonSem(int n, int flags)    
{
   key_t key = ftok(PATH_NAME, PROJ_ID);
   if(key < 0)
   {
       perror("ftok");
       return -1;
   }
   int semid = semget(key, n,flags);
   if(semid < 0)
   {
       perror("semget");
       return -1;
   }
   return semid;
}

int CreateSem(int n)
{
    return CommonSem(n, IPC_CREAT | IPC_EXCL | 0666);
}

int GetSem()
{
    return CommonSem(0, IPC_CREAT);
}

int DestroySem(int semid)
{
    int ret = semctl(semid, 0, IPC_RMID);
    if(ret < 0)
    {
        perror("semctl");
        return -1;
    }
    return 0;
}

int SetSemValue(int semid, int index, int value)
{ 
    union semun _semun;
    _semun.val = value;
    int ret = semctl(semid, index, SETVAL, _semun);
    if(ret < 0)
    {
        perror("semctl");
        return -1;
    }
    return 0;
}

int GetSemValue(int semid, int index, int *value)
{
    //semctl返回值就是当前value
    int ret = semctl(semid, index, GETVAL);
    if(ret < 0)
    {
        perror("semctl");
        return -1;
    }
    *value = ret;
    return 0;
}

int Commonop(int semid, int index, int n)
{
    //不能直接将信号量减一再设置回去，这样的操作不是原子操作
    //P、V操作应该都是原子操作。
    struct sembuf _sembuf;
    _sembuf.sem_num = index;
    _sembuf.sem_op = n;
    _sembuf.sem_flg = 0;
    int ret = semop(semid, &_sembuf, 1);
    if(ret < 0)
    {
        perror("semop");
        return -1;
    }
    return 0;
}

int P(int semid, int index)
{
    return Commonop(semid, index, -1);
}

int V(int semid, int index)
{
    return Commonop(semid, index, 1);
}

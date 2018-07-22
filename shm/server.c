#include "common.h"

int main()
{
    int shmid = CreateShm(1024);
    if(shmid < 0)
    {
        printf("CreateShm");
        return -1;
    }

    printf("shmid : %d\n",shmid);

    char *ptr = (char*)shmat(shmid, NULL, SHM_RDONLY);
    while(1)
    {
        printf("%s\n", ptr);
        sleep(1);
    }
    shmdt(ptr);
//    sleep(20);
//
//    int ret = DestroyShm(shmid);
//    if(ret < 0)
//    {
//        printf("DestroyShm");
//        return -1;
//    }
    return 0;
}

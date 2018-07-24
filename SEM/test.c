#include "common.h"

int main()
{
    //int semid = GetSem();
    int semid = CreateSem(10);
    if(semid < 0)
    {
        printf("CreateSem fail");
        return 1;
    }
    printf("semid = %d\n",semid);

    int ret = SetSemValue(semid, 0, 1);
    if(ret < 0)
    {
        printf("SetSemValue failed");
        return 1;
    }
   
    int value = 0;
    GetSemValue(semid, 0, &value);
    printf("after value expect 1, actual %d\n", value);

    P(semid, 0);
    GetSemValue(semid, 0, &value);
    printf("after value expect 1, actual %d\n", value);

    V(semid, 0);
    printf("---------释放了一个资源后--------\n");
   
    P(semid, 0);
    GetSemValue(semid, 0, &value);
    printf("-------haha--------\n");

    DestroySem(semid);
    return 0;
}


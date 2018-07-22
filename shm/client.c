#include "common.h"

int main()
{
    int shmid = GetShm();
    if(shmid < 0)
    {
        printf("GetShm");
        return -1;
    }
    printf("shmid: %d\n",shmid);
    // 0 表示
    char *ptr = (char*)shmat(shmid, NULL, 0);
    int i = 1;
    while(1)
    {
        int j = 0;
        while(j < i)
        {
            ptr[j] = 'A' + i - 1;
            j++;
        }
        ptr[j] = '\0';
        i++;
        i %= 26;
        sleep(1);
    }
    shmdt(ptr);
    return 0;
}

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *ThreadEntry(void *arg)
{
    (void)arg;
    while(1)
    {
        printf("I am thread1\n");
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, ThreadEntry, NULL);
    if(ret != 0)
    {
        //strerror 串进来一个错误码，返回一个可以读得懂的字符串
        printf("pthraed_create falied! %s\n", strerror(ret));
        return 1;
    }
    while(1)
    {
        //主线程是main
        printf("main thread\n");
    }
    return 0;
}

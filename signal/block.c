#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void MyHandler(int sig)
{
    printf("sig = %d\n",sig);
    return;
}

void PrintSigset(sigset_t *set)
{
    int i = 0;
    //只关注前31号信号
    for(; i <= 31; i++)
    {
        if(sigismember(set, i))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    printf("\n");
}

int main()
{
    signal(SIGINT, MyHandler);
    sigset_t new_set;
    sigset_t old_set;
    //初始化
    sigemptyset(&new_set);
    sigaddset(&new_set, SIGINT);
    sigprocmask(SIG_BLOCK, &new_set, &old_set);
    printf("sigprocmask done");
    while(1)
    {
        sigset_t pending_set;
        sigpending(&pending_set);
        sleep(1);
        PrintSigset(&pending_set);
    }
    return 0;
}

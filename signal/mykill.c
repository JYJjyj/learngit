#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("mykill [signo] [pid]\n");
        return 1;
    }
    int signo = atoi(argv[1]);
    int pid = atoi(argv[2]);
    int ret = kill(pid, signo);
    if(ret < 0)
    {
        perror("kill");
        return 1;
    }
    return 0;
}

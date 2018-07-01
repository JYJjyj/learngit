//从管道中读取数据
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ERR_EXIT(m)\
    do\
{\
    perror(m);\
    exit(EXIT_FAILURE);\
}while(0)

int main()
{
    int infd,outfd;
    outfd = open("back",O_CREAT | O_WRONLY | O_TRUNC,0644);
    if(outfd < 0)
        ERR_EXIT("open");

    infd = open("tp",O_RDONLY);
    if(infd < 0)
        ERR_EXIT("open");

    char buf[1024];
    int n;
    while((n = read(infd,buf,1024)) > 0)
    {
        write(outfd,buf,n);
    }
    close(infd);
    close(outfd);
    unlink("tp");
    return 0;
}

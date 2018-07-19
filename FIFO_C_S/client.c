//基于命名管道实现的客户端
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
int main()
{
    int wfd = open("mypipe",O_WRONLY);
    if(wfd < 0)
        perror("open");

    char buf[1024] = {0};
    while(1)
    {
        printf("please enter: ");
        fflush(stdout);
        ssize_t size = read(0,buf,sizeof(buf)-1);
        if(size <= 0)
            perror("read");
        else
            write(wfd, buf, strlen(buf));
    }
    close(wfd);
    return 0;
}

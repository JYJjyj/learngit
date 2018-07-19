#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    if(mkfifo("mypipe",0644) < 0)
    {
        perror("mkpipe");
    }

    int rfd = open("mypipe",O_RDONLY);
    if(rfd < 0)
        perror("open");

    char buf[1024] = {0};
    while(1)
    {
        printf("please wait...\n");
        ssize_t size = read(rfd, buf, sizeof(buf) - 1);
        if(size < 0)
            perror("read");
        else if(size == 0)
            printf("client quit!\n");
        else
            printf("client say: %s\n",buf);
    }
    close(rfd);
    return 0;
}

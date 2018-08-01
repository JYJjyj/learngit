#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc ,char *argv[])
{
    if(argc != 3)
    {
        printf("usage : ./client [ip] [port]");
    }
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        return 1;
    }
    
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]); 
    server.sin_port = htons(atoi(argv[2]));
    if(connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        perror("connect");
        return 2;
    }

    char buf[1024] = {0};
    while(1)
    {
        printf("please enter# ");
        fflush(stdout);
        ssize_t s = read(0, buf,  sizeof(buf) - 1);
        if(s > 0)
        {
            buf[s - 1] = 0;
            if(strcmp("quit",buf) == 0)
            {
                printf("client quit\n");
                break;
            }
            write(sock, buf, strlen(buf));
            s = read(sock, buf, sizeof(buf) - 1);
            buf[s] = 0;
            printf("server echo# %s\n", buf);
        }
    }
    close(sock);
    return 0;
}

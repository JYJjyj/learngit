#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX 128
void service(int sock, char *ip, int port)
{
    char buf[MAX];
    while(1)
    {
        ssize_t s = read(sock, buf, sizeof(buf) - 1);
        if(s < 0)
        {
            perror("read");
            return;
        }
        if(s == 0)
        {
            printf("client [%s:%d] quit!\n",ip, port);
            break;
        }
        else
        {   
            buf[s] = 0;
            printf("[%s:%d] say# %s\n",ip, port, buf);
            write(sock, buf, sizeof(buf) - 1);
        }
    }
}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("usage: ./server [ip] [port]");
        return 1;
    }
    //创建socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        perror("socket");
        return 1;
    }
    //绑定端口号
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));
    
    if(bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        return 1;
    }
    
    //监听
    if(listen(sockfd, 5) < 0)
    {
        perror("listen!");
        return 1;
    }
    
    //将响应返回给socket
    struct sockaddr_in peer;
    while(1)
    {
        socklen_t len = sizeof(peer);
        int new_sock = accept(sockfd, (struct sockaddr*)&peer, &len);
        if(new_sock < 0)
        {
            perror("accept");
            continue;
        }
        printf("get a new connnect, [%s:%d]\n",inet_ntoa(peer.sin_addr) ,ntohs(peer.sin_port));
        service(new_sock, inet_ntoa(peer.sin_addr), ntohs(peer.sin_port));
        close(new_sock);
    }
}

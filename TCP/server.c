#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#define MAX 128

typedef struct 
{
    int sock;
    char ip[24];
    int port;
}net_info_t;
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

void *thread_service(void *arg)
{
    net_info_t *p = (net_info_t*)arg;
    service(p->sock, p->ip, p->port);
    close(p->sock);
    free(p);
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

        net_info_t *p = (net_info_t*)malloc(sizeof(net_info_t));
        if(p == NULL)
        {
            perror("malloc");
            close(new_sock);
            continue;
        }
        p->sock = new_sock;
        strcpy(p->ip,inet_ntoa(peer.sin_addr));
        p->port = ntohs(peer.sin_port);
        pthread_t tid;
        pthread_create(&tid, NULL,thread_service, (void*)p);
        pthread_detach(tid);
       // pid_t pid = fork();
       // if(pid == 0)
       // {
       //     close(sockfd);

       //     if(fork() > 0)
       //         exit(0);
       //     service(new_sock, inet_ntoa(peer.sin_addr), ntohs(peer.sin_port));
       //     close(new_sock);
       //     exit(0);
       // }
       // else if(pid > 0)
       // {
       //     close(new_sock);
       //     waitpid(pid,NULL,0);
       // }
       // else
       // {
       //     printf("fork erroe!\n");
       //     continue;
       // }
    }
}

/////////////////////////////////////////////////////////
//实现一个建议版本的HTTP服务器，功能是不管发送
//什么样的请求都返回hello world网页
//HTTP协议在传输层使用的是TCP
/////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;

int ServerInit(const char* ip, short port)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0)
    {
        perror("socket");
        return -1;
    }
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    int ret = bind(fd, (sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        return -1;
    }
    ret = listen(fd, 5);
    if(ret < 0)
    {
        perror("listen");
        return -1;
    }
    return fd;
}

void *ThreadEntry(void *arg)
{
    int64_t new_sock = (int64_t)arg;
    //1. 读取并解析数据（由于此处不管请求是啥样的都返回helloworld）
    //  所以此处将解析过程省略
    char buf[1024 * 10] = {0};  //10k
    ssize_t size = read(new_sock, buf, sizeof(buf) - 1);
    printf("[Request] %s \n",buf);
    if(size < 0)
    {
        perror("read");
        return (void*)-1;
    }
    //2.构造一个hello world响应字符串，并写回客户端
    const char* first_line = "HTTP/1.1 200 OK\n";
    const char* blank_line = "\n";
    const char* body = "<html> hello world</html>";
    char header[1024 * 10] = {0};
    sprintf(header, "Content-Type: text/html;\nContent-Length: %lu\n",strlen(body));
    write(new_sock, first_line, strlen(first_line));
    write(new_sock, header, strlen(header));
    write(new_sock, blank_line, strlen(blank_line));
    write(new_sock, body, strlen(body));
    return NULL;
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("usage: ./server [ip] [port]\n");
        return 1;
    }
    int listen_sock = ServerInit(argv[1], atoi(argv[2]));
    if(listen_sock < 0)
    {
        printf("ServerInit failed\n");
        return 1;
    }
    printf("ServerInit OK\n");
    while(1)
    {
        sockaddr_in peer;
        socklen_t len = sizeof(peer);
        int64_t new_sock = accept(listen_sock, (sockaddr*)&peer, &len);
        if(new_sock < 0)
        {
            perror("accept");
            continue;
        }
        pthread_t tid;
        pthread_create(&tid, NULL, ThreadEntry, (void*)new_sock);
    }
    return 0;
}

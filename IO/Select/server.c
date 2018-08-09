#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <arpa/inet.h>

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

//////////////////////////////////////////////////////////////////////////////////////
//对fd_set 进行一个简单的封装
//能够方便的获取到文件描述符集中的最大的文件描述符
//////////////////////////////////////////////////////////////////////////////////////

typedef struct FdSet
{
    fd_set fds;
    int max_fd;     //当前文件描述符集中最大的文件描述符
}FdSet;

void FdSetInit(FdSet* set)
{
    if(set == NULL)
        return;
    set->max_fd = -1;
    FD_ZERO(&set->fds);
}

void FdSetAdd(FdSet* set, int fd)
{
    FD_SET(fd, &set->fds);
    if(fd > set->max_fd)
    {
        set->max_fd = fd;
    }
}

void FdSetDel(FdSet* set, int fd)
{
    FD_CLR(fd, &set->fds);
    int max_fd = -1;
    int i = 0;
    for(;i <= set->max_fd; ++i)
    {
        if(!FD_ISSET(i, &set->fds))
        {
            continue;
        }
        if(i > max_fd)
        {
            max_fd = i;
        }
    }
    //循环结束之后， max_fd里面就是当前最大的文件描述符
    set->max_fd = max_fd;
    return;
}

int ServerStart(const char* ip, short port)
{
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_sock < 0)
    {
        perror("socket");
        return -1;
    }
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    int ret = bind(listen_sock, (sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        return -1;
    }

    ret = listen(listen_sock, 5);
    if(ret < 0)
    {
        perror("listen");
        return -1;
    }
    return listen_sock;
}

int ProcessRequest(int new_sock)
{
    //完成对客户端的读写操作
    //此处只进行一次读写，所有的等待操作都交给select来完成
    //下一次对该socket读写的时机，也是由select来进行通知的
    //也就是下一次返回该文件描述符就绪的时候，就能进行读数据了
    char buf[1024] = {0};
    ssize_t read_size = read(new_sock, buf, sizeof(buf) - 1);
    if(read_size < 0)
    {
        perror("read");
        return -1;
    }
    if(read_size == 0)
    {
        printf("read done!\n");
        printf("[client %d] disconnect\n",new_sock);
        return 0;
    }
    buf[read_size] = '\0';
    printf("[client %d] say: %s\n",new_sock, buf);
    write(new_sock, buf, strlen(buf));
    return read_size;
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("usage : ./server [ip] [port]\n");
        return 1;
    }
    //1.对服务器进行初始化
    int listen_sock = ServerStart((const char*)argv[1], atoi(argv[2]));
    if(listen_sock < 0)
    {
        printf("ServerStart failed\n");
        return 1;
    }
    printf("server start ok\n");
    //2.进入事件循环
    FdSet read_fds;
    FdSetInit(&read_fds);
    FdSetAdd(&read_fds, listen_sock);
    while(1)
    {
        //3.使用select完成等待
        //创建一个output_fds 最主要的目的是为了防止select返回
        //把read_fds 中的结果破坏掉，导致其中的数据丢失
        //把read_fds 中的结果破坏掉，导致其中的 数据丢失
        //read_fds 始终表示select监控的文件描述符集的内容
        
        FdSet output_fds = read_fds;
        int ret = select(output_fds.max_fd + 1, &output_fds.fds, NULL, NULL, NULL);

        if(ret < 0)
        {
            perror("select");
            continue;
        }
        //4.select返回之后进行处理，分两种情况
        //  a）listen_sock 读就绪,就调用accept
        //  b）new_sock读就绪，就调用read
        if(FD_ISSET(listen_sock, &output_fds.fds))
        {
            //调用accept获取到连接,把new_sock加入到select之中
            sockaddr_in peer;
            socklen_t len = sizeof(peer);
            int new_sock = accept(listen_sock, (sockaddr*)&peer, &len);
            if(new_sock < 0)
            {
                perror("accept");
                continue;
            }
            FdSetAdd(&read_fds, new_sock);
            printf("[client %d] connect!\n",new_sock);
        }
        else
        {
            int i =0;
            for(; i < output_fds.max_fd + 1; ++i)
            {
                //进行读写
                if(!FD_ISSET(i, &output_fds.fds))
                {
                    continue;
                }
                // i 就是位图中的一位，就可以进行读写了
                int ret = ProcessRequest(i);
                if(ret == 0)
                {
                    FdSetDel(&read_fds, i);
                    close(i);
                }
            }
        }
    }
    return 0;
}

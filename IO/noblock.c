#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

//把文件描述符设置为非阻塞
int SetNoBlock(int fd)
{
    //flag理解为一个位图，其中的每一位都分别代表不同的含义
    //不能上来及直接进行SETFL，我们期望的是只把文件描述符
    //设置为非阻塞，而其他的选项不应该受到影响
    int flag = fcntl(fd, F_GETFL);
    if(flag < 0)
    {
        perror("fcntl get");
        return -1;
    }
    int ret = fcntl(fd, F_SETFL, flag | O_NONBLOCK);
    if(ret < 0)
    {
        perror("fcntl set");
        return -1;
    }
    return ret;
}

int main()
{
    SetNoBlock(0);
    while(1)
    {
        char buf[1024] = {0};
        //设置成非阻塞IO之后，如果数据还没有准备好，
        //read就会立刻返回，并且返回一个错误码
        ssize_t size = read(0, buf, sizeof(buf) - 1);
        if(size < 0)
        {
            sleep(1);
            perror("read");
            continue;
        }
        else if(size == 0)
        {
            printf("read done!");
            return 0;
        }
        buf[size] = '\0';
        printf("user input: %s\n",buf);
        sleep(1);
    }
    return 0;
}

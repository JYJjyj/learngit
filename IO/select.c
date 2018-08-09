#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    //1.先把文件描述符准备好，
    while(1)
    {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(0, &fds);
        int ret = select(1, &fds, NULL, NULL, NULL);
        if(ret < 0)
        {
            perror("select");
            return 1;
        }
        //如果select返回了，并且不是错误返回， 只有一种可能，就是0号
        //文件描述符读就绪了。
        char buf[1024] = {0};
        ssize_t read_size = read(0, buf, sizeof(buf) - 1);
        if(read_size < 0)
        {
            perror("read");
            return 1;
        }
        if(read_size == 0)
        {
            printf("read done");
            return 0;
        }
        buf[read_size] = '\0';
        printf("user write %s\n",buf);
    }
    return 0;
}

//匿名管道的创建与使用
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ERR_EXIT(m)\
    do\
{\
    perror(m);\
    exit(EXIT_FAILURE);\
}while(0)

int main()
{
    //1.创建管道
    int fd[2];
    char buf1[1024] = {0};
    if(pipe(fd) == -1)
    {
        perror("pipe");
        exit(1);
    }
    //2.创建子进程
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork");
        ERR_EXIT("fork error");
    }
    //3.父进程写数据到管道
    if(pid > 0)
    {
        close(fd[0]);      //关闭管道的读端
        fgets(buf1,100,stdin);
        write(fd[1],buf1,strlen(buf1));
        close(fd[1]);
        exit(EXIT_SUCCESS);
    }
    //4. 子进程从管道中读数据并输出到屏幕上
    if(pid == 0)
    {
        close(fd[1]);
        char buf[10] = {0};
        read(fd[0],buf,6);
        printf("%s\n",buf);
    }
    return 0;
}

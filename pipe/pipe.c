//匿名管道
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int fd[2];
    char buf[100] = {};
    int len;
    //1.创建管道
    if(pipe(fd) == -1)
    { 
        perror("pipe error!");
        exit(1);
    }
    //2.从标准输入读入数据到buf
    while(fgets(buf,100,stdin))
    {
        len = strlen(buf);
        if(write(fd[1],buf,len) != len)
        {
            perror("write!");
            break;
        }
        //将管道的数据置0，避免为随机值
        memset(buf,0x00,sizeof(buf));
    //3.打开管道的读端，从管道中读取数据
        if((len = read(fd[0],buf,100)) == -1)
        {
            perror("read!");
            break;
        }
    //4.将读到的数据打印到标准输出上
        if(write(1,buf,len) != len)
        {
            perror("write to stdout!");
            break;
        }
    }
    return 0;
}

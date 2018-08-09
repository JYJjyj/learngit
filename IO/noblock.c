#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
    while(1)
    {
        char buf[1024] = {0};
        ssize_t size = read(0, buf, sizeof(buf) - 1);
        if(size < 0)
        {
            perror("read");
            return 1;
        }
        else if(size == 0)
        {
            printf("read done!");
            return 0;
        }
        buf[size] = '\0';
        printf("user input: %s\n",buf);
    }
    return 0;
}

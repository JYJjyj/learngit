#include <stdio.h>
#include <unistd.h>
#include "common.h"
#include <string.h>
int main()
{
    int msgid = GetMsg();
    printf("msgid: %d\n", msgid);
    while(1)
    {
        char buf[2048] = {0};
        printf("input> ");
        fflush(stdout);
        ssize_t read_size = read(0, buf, sizeof(buf) - 1);
        if(read_size < 0)
        {
            perror("read");
            return 1;
        }
        if(read_size == 0)
        {
            printf("read done\n");
            return 0;
        }
        buf[read_size] = '\0';

        int ret = sendMsg(msgid, CLIENT_TYPE, buf, strlen(buf));
        if(ret < 0)
        {
            perror("sendmsg\n");
            return 1;
        }
    }
    return 0;
}


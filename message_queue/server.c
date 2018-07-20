#include <stdio.h>
#include <unistd.h>
#include "common.h"

int main()
{
    int msgid = CreateMsg();
    printf("msgid = %d\n", msgid);
    while(1)
    {
        char buf[2048] = {0};
        int ret = recvMsg(msgid, CLIENT_TYPE, buf, sizeof(buf) - 1);
        if(ret < 0)
        {
            perror("recvMsg");
            return 1;
        }
        printf("client say: %s",buf);
    }
    //DestroyMsg(msgid);
    return 0;
}


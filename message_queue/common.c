#include "common.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

int CommonMsg(int flags)
{
    key_t key = ftok(PATHNAME, PROJ_ID);
    if(key == -1)
    {
        perror("ftok");
        return -1;
    }
    int msgid = msgget(key, flags); // 0666表示权限，所有用户可读可写 
     //IPC_EXCL要搭配IPC_CREAT使用，意思是要是消息队列不存在就创建, 存在就创建失败。
    if(msgid < 0)
    {
        perror("msgget");
        return -1;
    }
    return msgid;
}

int CreateMsg()
{
    return CommonMsg(IPC_CREAT | IPC_EXCL | 0666);
}

int GetMsg()
{
    return CommonMsg(IPC_CREAT);
}

int DestroyMsg(int msgid)
{
    int ret = msgctl(msgid, IPC_RMID, NULL);
    if(ret < 0)
    {
        perror("msgctl");
        return -1;
    }
    return 0;
}

int sendMsg(int msgid, long type, char* buf, size_t size)
{
   Msgbuf msgbuf;
   if(size >= sizeof(msgbuf.mtext))
   {
       printf("size is to large!\n");
       return -1;
   }
   msgbuf.mtype = type;
   strcpy(msgbuf.mtext, buf);
   int ret = msgsnd(msgid, &msgbuf, sizeof(msgbuf.mtext), 0);
   if(ret < 0)
   {
       perror("msgsnd");
       return -1;
   }
   return 0;
}

int recvMsg(int msgid, long type, char *buf, size_t max_size)
{
    Msgbuf msgbuf;
    ssize_t ret = msgrcv(msgid, &msgbuf, sizeof(msgbuf.mtext), type, 0);
    if(ret < 0)
    {
        perror("msgrcv");
        return -1;
    }
    if(max_size < sizeof(msgbuf.mtext))
    {
        printf("buf is too small");
        return -1;
    }
    strcpy(buf, msgbuf.mtext);
    return 0;
}

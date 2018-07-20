#pragma once
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define PATHNAME "."
#define PROJ_ID 0x6666

#define SERVER_TYPE 1
#define CLIENT_TYPE 2

typedef struct Msgbuf{
    long mtype;        // 数据的类型 
    char mtext[1024];  // 存储数据的字符串数组
}Msgbuf;

//创建一个消息队列，如果已经存在，就调用失败
int CreateMsg();

//打开一个已有的消息队列，如果不存在，也返回失败
int GetMsg();

//销毁一个消息队列
int DestroyMsg(int msgid);

int sendMsg(int msgid, long type, char *buf, size_t size);

int recvMsg(int msgid, long type, char *buf, size_t max_size);

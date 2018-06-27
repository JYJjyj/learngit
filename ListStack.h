#pragma once
//链表实现的栈（链式栈）
#include<stdio.h>
#include<malloc.h>
#include<assert.h>

typedef char DataType;

typedef struct ListNode
{
    DataType data;
    struct ListNode* _next;
}ListNode;


//初始化 
void ListStackInit(ListNode **l);
//销毁 
void ListStackDestroy(ListNode *l);
//入栈 
void ListStackPush(ListNode *l,DataType data);
//出栈 
void ListStackPop(ListNode *l);
//取栈顶元素 
DataType ListStackTop(ListNode l);

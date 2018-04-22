//c语言实现一个双链表
#pragma once

typedef char DLinkType; 

typedef struct DLinkNode { 
DLinkType data; 
struct DLinkNode* next; 
struct DLinkNode* prev; 
} DLinkNode; 

void DLinkListInit(DLinkNode** head); 

DLinkNode* DLinkListPushBack(DLinkNode* head, DLinkType value); 

void DLinListPopBack(DLinkNode* head); 

void DLinkListPushFront(DLinkNode* head, DLinkType value); 

void DLinkListPopFront(DLinkNode* head);

DLinkNode* DLinkListFind(DLinkNode* head, DLinkType to_find); 

/** 
* @brief 往指定位置之前插入一个元素 
*/ 
void DLinkListInsert(DLinkNode* pos, DLinkType value); 

/** 
* @brief 往指定位置之后插入一个元素 
*/ 
void DLinkListInsertAfter(DLinkNode* pos, DLinkType value);

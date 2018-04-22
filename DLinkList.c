//带头结点的双向链表
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include"DLinkList.h"
//typedef struct DLinkNode { 
//DLinkType data; 
//struct DLinkNode* next; 
//struct DLinkNode* prev; 
//} DLinkNode; 
//初始化一个双链表
void DLinkListInit(DLinkNode** head)
{
    assert(head);
    (*head) = (DLinkNode*)malloc(sizeof(DLinkNode));
    (*head)->next = NULL;
    (*head)->prev = NULL;
}
//创建一个结点
DLinkNode* CreateNode(DLinkType value)
{
    DLinkNode* ret = (DLinkNode*)malloc(sizeof(DLinkNode));
    ret->data = value;
    ret->next = NULL;
    ret->prev = NULL;
    return ret;
}
//销毁一个结点
void DestroyNode(DLinkNode *ptr)
{
    free(ptr);
    ptr = NULL;
}
//双链表的尾插
DLinkNode* DLinkListPushBack(DLinkNode* head, DLinkType value)
{
    assert(head != NULL);
    DLinkNode *newnode = CreateNode(value);
    newnode->next = NULL;
    DLinkNode *end = head;
    while(end->next != NULL)
    {
        end = end->next;
    }
    end->next = newnode;
    newnode->prev = end;
    return newnode;
}
// 尾删
void DLinListPopBack(DLinkNode* head)
{
    assert(head);
    DLinkNode *tmp = head;
    if(tmp->next == NULL)
        return;
    if(tmp->next->next == NULL)
    {
        DestroyNode(tmp->next);
        head->next = NULL;
        return;
    }
    while(tmp->next->next)
    {
        tmp = tmp->next;
    }
    DestroyNode(tmp->next);
    tmp->next = NULL;
}
//头插
void DLinkListPushFront(DLinkNode* head, DLinkType value)
{
    assert(head);
    DLinkNode *newnode = CreateNode(value);
    if(head->next == NULL)
    {
        head->next = newnode;
        newnode->next = NULL;
        newnode->prev = head;
        return;
    }
    newnode->next = head->next;
    head->next->prev = newnode;
    head->next = newnode;
    newnode->prev = head;
}
//头删
void DLinkListPopFront(DLinkNode* head)
{
    assert(head);
    //只有一个头节点
    if(head->next == NULL)
    {
        return;
    }
    DLinkNode *to_delete = head->next;
    head->next = to_delete->next;
    DestroyNode(to_delete);
    if(head->next!=NULL)
    {
        head->next->prev = head;
    }
}
//在链表中查找
DLinkNode* DLinkListFind(DLinkNode* head, DLinkType to_find)
{
    assert(head);
    if(head->next == NULL)
        return NULL;
    DLinkNode *tmp = head->next;
    while(tmp)
    {
        if(tmp->data == to_find)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}
//
///** 
//* @brief 往指定位置之前插入一个元素 
//*/ 
void DLinkListInsert(DLinkNode* pos, DLinkType value)
{
    assert(pos);
    DLinkNode *newnode = CreateNode(value);
    newnode->next = pos;
    newnode->prev = pos->prev;
    pos->prev = newnode;
    newnode->prev->next = newnode;
}
//
///** 
//* @brief 往指定位置之后插入一个元素 
//*/ 
void DLinkListInsertAfter(DLinkNode* pos, DLinkType value)
{
    assert(pos);
    DLinkNode *newnode = CreateNode(value);
    newnode->prev = pos;
    newnode->next = pos->next;
    pos->next = newnode;
    newnode->next->prev = newnode;
}
void PrintList(DLinkNode *head)
{
    assert(head);
    printf("[head] ");
    DLinkNode *tmp = head->next;
    if(tmp == NULL)
        return;
    while(tmp != NULL)
    {
        printf("[%c] ",tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}

////////////////////////////测试代码/////////////
#define TESTHEAD printf("------------------------------------------%s------------------------------------------\n",__FUNCTION__);

void testPushBack()
{
    TESTHEAD;
    DLinkNode *head;
    DLinkListInit(&head);
    DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'b');
    DLinkListPushBack(head,'c');
    DLinkListPushBack(head,'d');
    DLinkListPushBack(head,'e');
    PrintList(head);
}
void testPopBack()
{
    TESTHEAD;
    DLinkNode *head;
    DLinkListInit(&head);
    DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'b');
    DLinkListPushBack(head,'c');
    DLinkListPushBack(head,'d');
    DLinkListPushBack(head,'e');
    printf("尾删前：");
    PrintList(head);
    DLinListPopBack(head);
    printf("尾删后：");
    PrintList(head);
}
void testPushFront()
{
    TESTHEAD;
    DLinkNode *head;
    DLinkListInit(&head);
    DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'b');
    DLinkListPushBack(head,'c');
    DLinkListPushBack(head,'d');
    DLinkListPushBack(head,'e');
    printf("头插前：");
    PrintList(head);
    DLinkListPushFront(head,'1');
    printf("头插后：");
    PrintList(head);
}
void testPopFront()
{
    TESTHEAD;
    DLinkNode *head;
    DLinkListInit(&head);
    DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'b');
    DLinkListPushBack(head,'c');
    DLinkListPushBack(head,'d');
    DLinkListPushBack(head,'e');
    printf("头删前：");
    PrintList(head);
    DLinkListPopFront(head);
    printf("头删后：");
    PrintList(head);
    printf("\n");
}
void testFind()
{
    TESTHEAD;
    DLinkNode *head;
    DLinkNode *ret;
    DLinkListInit(&head);
    DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'b');
    DLinkListPushBack(head,'c');
    DLinkListPushBack(head,'d');
    DLinkListPushBack(head,'e');
    PrintList(head);
    ret = DLinkListFind(head,'f');
    if(ret)
    {
        printf("找到了！\n");
    }
    else
        printf("没找到！\n");
}
void testInsert()
{
    TESTHEAD;
    DLinkNode *head;
    DLinkNode *pos ;
    DLinkListInit(&head);
    pos = DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'b');
    DLinkListPushBack(head,'c');
    DLinkListPushBack(head,'d');
    DLinkListPushBack(head,'e');

    DLinkListInsert(pos,'x');
    PrintList(head);
}
void testInsertAfter()
{
    TESTHEAD;
    DLinkNode *head;
    DLinkNode *pos;
    DLinkListInit(&head);
    pos = DLinkListPushBack(head,'a');
    DLinkListPushBack(head,'b');
    DLinkListPushBack(head,'c');
    DLinkListPushBack(head,'d');
    DLinkListPushBack(head,'e');
    DLinkListInsertAfter(pos,'x');
    PrintList(head);
}
void test()
{
    testPushBack();
    testPopBack();
    testPushFront();
    testPopFront();
    testFind();
    testInsert();
    testInsertAfter();
}

int main()
{
    test();
    return 0;
}

#include "ListStack.h"

//初始化 
void ListStackInit(ListNode **l)
{
    //初始化头节点
    assert(l);
    (*l) = (ListNode*)malloc(sizeof(ListNode));
    (*l)->_next = NULL;
}
//创建一个结点
ListNode* CreateNode(DataType value)
{
    ListNode *newnode = (ListNode*)malloc(sizeof(ListNode));
    newnode->data = value;
    newnode->_next = NULL;
    return newnode;
}
//销毁一个结点
void DestroyNode(ListNode *p)
{
    assert(p);
    free(p);
    p = NULL;
}
//销毁 
void ListStackDestroy(ListNode *l)
{
    assert(l);
    if(l->_next == NULL)
        return;
    ListNode *tmp = l;
    while(tmp != NULL)
    {
        ListNode *next = tmp->_next;
        DestroyNode(tmp);
        tmp = next;
    }
    l->_next = NULL;
}
//入栈 
void ListStackPush(ListNode *l,DataType data)
{
    //头插
    assert(l);
    ListNode *newnode = CreateNode(data);
    newnode->_next = l->_next;
    l->_next = newnode;
}
//出栈 
void ListStackPop(ListNode *l)
{
    assert(l);
    if(l->_next == NULL)
        return;
    ListNode *tmp = l->_next;
    l->_next = tmp->_next;
    DestroyNode(tmp);
}
//取栈顶元素 
DataType ListStackTop(ListNode l)
{
    assert(l._next);
    return (l._next->data);
}
//打印栈
void PrintStack(ListNode l)
{
    ListNode *tmp = (&l)->_next;
    printf("[head] ");
    while(tmp != NULL)
    {
        printf("[%c] ",tmp->data);
        tmp = tmp->_next;
    }
    printf("\n");
}
//////////////////////测试代码////////////////////////////////////////////////
#define TESTHEAD printf("-------------------------------%s---------------------------------------\n",__FUNCTION__)

void testPush()
{
    TESTHEAD;
    ListNode *l = NULL;
    ListStackInit(&l);
    ListStackPush(l,'a');
    ListStackPush(l,'b');
    ListStackPush(l,'c');
    ListStackPush(l,'d');
    ListStackPush(l,'e');
    PrintStack(*l);
}
void testPop()
{
    TESTHEAD;
    ListNode *l = NULL;
    ListStackInit(&l);
    ListStackPush(l,'a');
    ListStackPush(l,'b');
    ListStackPush(l,'c');
    ListStackPush(l,'d');
    ListStackPush(l,'e');
    PrintStack(*l);
    ListStackPop(l);
    ListStackPop(l);
    PrintStack(*l);
}
void testDestroy()
{
    TESTHEAD;
    ListNode *l = NULL;
    ListStackInit(&l);
    ListStackPush(l,'a');
    ListStackPush(l,'b');
    ListStackPush(l,'c');
    ListStackPush(l,'d');
    ListStackPush(l,'e');
    PrintStack(*l);
    ListStackDestroy(l);
    PrintStack(*l);
}
void testTop()
{
    TESTHEAD;
    ListNode *l = NULL;
    ListStackInit(&l);
    ListStackPush(l,'a');
    ListStackPush(l,'b');
    ListStackPush(l,'c');
    ListStackPush(l,'d');
    ListStackPush(l,'e');
    PrintStack(*l);
    DataType ret = ListStackTop(*l);
    printf("栈顶元素：%c \n",ret);
}
void test()
{
  testPush();
  testPop();
  testDestroy();
  testTop();
}
int main()
{
    test();
    return 0;
}

#include <iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
//注意整理格式(定义声明分离)
typedef int DataType; 
struct ListNode 
{ 
    ListNode* _next; 
    ListNode* _prev; 
    DataType _data;
    ListNode(DataType x) 
        :_next(NULL) 
         ,_prev(NULL) 
         ,_data(x) 
    {} 
}; 
//带头双链表
class List 
{ 
    typedef ListNode Node; 
public: 
    List() 
        :_head(new Node(DataType())) 
    { 
        _head->_next = _head; 
        _head->_prev = _head; 
    } 

    List(const List& l)
        :_head(new Node(DataType())) 
    { 
       _head->_next = _head; 
       _head->_prev = _head; 
       Node *cur =l._head->_next;
       Node *prev = NULL;
       Node *tmp = _head;
       while(cur != l._head)
       {
           prev = tmp;
           tmp = new Node(cur->_data);
           tmp->_prev = prev;
           prev->_next = tmp;
           cur=cur->_next;
       }
       tmp->_next = _head;
       _head->_prev = tmp;
    } 
List& operator=(List l)
{
    //现代写法
    Node *tmp = _head;
    _head = l._head;
    l._head = tmp;
    return *this;
}
~List()
{
    Node *tmp = _head->_next;
    while(tmp != _head)
    {
        Node *cur = tmp->_next;
        delete tmp;
        tmp = cur;
    }
}
//尾插
void PushBack(DataType x)
{
//    Node *tmp = _head->_prev;
//    Node *newnode = new Node(x);
//    tmp->_next = newnode;
//    newnode->_prev = tmp;
//    newnode->_next = _head;
//    _head->_prev = newnode;
    Insert(_head->_prev,x);
}
//头插
void PushFront(DataType x)
{
//    Node *newnode = new Node(x);
//   newnode->_next = _head->_next;
//   _head->_next = newnode;
//   newnode->_prev = _head;
//   newnode->_next->_prev = newnode;
   Insert(_head->_next,x);
}
//尾删
void PopBack()
{
//    Node *cur = _head->_prev;
//    cur->_prev->_next = _head;
//    _head->_prev = cur->_prev;
//    delete cur;
    Erase(_head->_prev);
}
//头删
void PopFront()
{
//    if(_head->_next==_head)
//        return;
//    Node *tmp = _head->_next->_next;
//    delete _head->_next;
//    _head->_next = tmp;
//    tmp->_prev = _head;
    Erase(_head->_next);
}
Node* Find(DataType x)
{
    if(_head->_next == _head)
        return NULL;
    Node *cur = _head->_next;
    while(cur != _head)
    {
        if(cur->_data == x)
            return cur;
        cur=cur->_next;
    }
    return NULL;
}
void Insert(Node* pos, DataType x)
{
    Node *newnode = new Node(x);
    newnode->_next = pos;
    pos->_prev->_next = newnode;
    newnode->_prev = pos->_prev;
    pos->_prev = newnode;
}
void Erase(Node* pos)
{
    Node *next = pos->_next;
    Node *prev = pos->_prev;
    delete pos;
    next->_prev = prev;
    prev->_next = next;
}
void Print()
{
    Node *tmp = _head->_next;
    while(tmp != _head)
    {
        printf("[%d] ",tmp->_data);
        tmp = tmp->_next;
    }
    printf("\n");
}
private: 
Node* _head; 
}; 
int main()
{
    List l;
    l.PushFront(1);
    l.PushBack(2);
    l.PushBack(3);
    l.PushBack(4);
    l.PushBack(5);
    l.PushBack(6);
    List l1;
    l1=l;
    l.Print();
    l1.Print();
    l.PushFront(0);
    l.Print();
    l.PopBack();
    l.Print();
    l.PopFront();
    l.Print();
    ListNode *ret = l.Find(3);
    cout<<ret->_data<<endl;
    cout<<ret->_next->_data<<endl;
}

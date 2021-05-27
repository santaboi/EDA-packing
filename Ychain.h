#ifndef YCHAIN_H
#define YCHAIN_H
#include<iostream>



typedef struct Ynode
{
    double Xl=0;
    double Xr=0;
    double Yt=0;
    struct Ynode* next=NULL;
    struct Ynode* previous=NULL;
}Node;  


class Ychain
{
private:
public:
    Node* first;
    void create1(Node*a);//create chain 把first 接上第一個Ynode
    void create();
    void insert(Node *a,Node*b);//將node b 插在node a後面
    void operation(double x1,double x2,double h1);
    void del(Node *b);//將node b delete ,node a 是b的previous node
    void currentToFirst();
    void curNext();
    void firstChange(Node *a);

    Node* currentPtr;
};

void Ychain::create1(Node*a)
{
    first=a;
    currentPtr=first;
}

void Ychain::create()
{
    first=new Node();
}

void Ychain::insert(Node *a,Node*b)
{
    b->next=a->next;
    a->next->previous=b;
    b->previous=a;
    a->next=b;
}

void Ychain::operation(double x1,double x2,double h1)
{

}




void Ychain::del(Node *b)
{
    if(b==first) 
    {first=first->next;
     first->next->previous=NULL;
    }
    else b->previous->next=b->next;
    delete b;
}

void Ychain::currentToFirst()
{
    currentPtr=first;
}

void Ychain:: curNext()
{
    currentPtr=currentPtr->next;
}

void Ychain ::firstChange(Node*a)
{
    first=a;
}


#endif
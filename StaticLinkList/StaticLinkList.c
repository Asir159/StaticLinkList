#include <stdio.h>

#define MAXSIZE 1000

#define ERROR 0
#define OK 1

typedef int Status;
typedef char Elmtype;

/*创建静态线性链表*/
typedef struct Compoent
{
    Elmtype data;
    int cur;            //光标位置
}StaticLinkList[MAXSIZE];

/*初始化线性表  将链表各分量链成一个备用链表,space[0]为头指针, "0"代表空指针*/
Status InitList(StaticLinkList space)
{
    int i = 0;
    for(i=0; i<MAXSIZE-1; i++)
    {
        space[i].cur = i+1;
    }
    space[MAXSIZE-1].cur = 0;        //目前链表为空，最后一的cur为0

    return OK;
}

int ListLength(StaticLinkList L)
{
    int i,j;
    j = 0;
    //将插入最后的元素的下标给i,找到第一个(头节点)下标结束
    i = L[MAXSIZE-1].cur;
    while(i)
    {
        i = L[i].cur;           //假如前面有2个数据元素:i=2,它们分别 2 1 0,其中头节点 "0" 不进行长度计算
        j++;
    }
    return j;

}

/*表用空间不为空表,将备用空间给节点下标*/
int malloc_SSL(StaticLinkList space)
{
    int i = 0;
    i = space[0].cur;                
    if(space[0].cur)
        space[0].cur = space[i].cur;

    return i;
}

void visit(Elmtype e)
{
    printf("%c",e);
}

Status ListTraverse(StaticLinkList L)
{
    int i;

    i = L[MAXSIZE-1].cur;
    while(i)
    {
        visit(L[i].data);
        i = L[i].cur;
    }
    printf("\n");
    return OK;
}

Status InsertList(StaticLinkList L,int i,Elmtype e)
{
    int j,k,l;
    if(i<1 || i>ListLength(L)+1)            //i不能小于1 或者大于长度+1  初始长度为0需要+1
        return ERROR;
    k = MAXSIZE - 1;
    j = malloc_SSL(L);

    if(j)
    {
        L[j].data = e;     
       for(l=1;l<=i-1;l++)
       {
            k = L[k].cur;           //寻找第i个元素
       }
        L[j].cur = L[k].cur;            
        L[k].cur = j;
        return OK;
    }
    return ERROR;
}

void free_SSL(StaticLinkList space, int i)
{
    space[i].cur = space[0].cur;
    space[0].cur = i;
}

Status ListDelte(StaticLinkList L , int i)
{
    int k,j;
    j = 1;
    if(i<1 || i>ListLength(L)+1)
        return ERROR;
    
    k = MAXSIZE-1;
    for(j=1;j<=i-1;j++)
    {
        k = L[k].cur;
    }
    j = L[k].cur;
    L[k].cur = L[j].cur;
    free_SSL(L,j);

    return OK;
}

int main()
{
    StaticLinkList L;

    InitList(L);
    printf("初始化链表ListLength(L)为:%d\n",ListLength(L));

   InsertList(L,1,'A');
   InsertList(L,2,'B');
   //InsertList(L,1,'C');
   InsertList(L,3,'D');
   InsertList(L,4,'E');
   InsertList(L,5,'F');
    printf("在表头插入ABCDEF后 L.data\n");
    ListTraverse(L);

    InsertList(L,3,'C');
    printf("在'B'与'D'间插入'C'后L.data\n");
    ListTraverse(L);

    ListDelte(L,1);
    printf("在A后L.data\n");
    ListTraverse(L);

    return 0;
}
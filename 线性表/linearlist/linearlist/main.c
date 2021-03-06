//
//  main.c
//  linearlist
//
//  Created by matthew on 2017/5/25.
//  Copyright © 2017年 matthew. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define  OK  1
#define  OK  1
#define  TRUE  1
#define  FALSE  0
#define  ERROR  -1å
#define  OVERFLOW  -2
#define  LIST_INIT_SIZE  100
#define  LISTINCREMENT  10
typedef int ElemType;
typedef int Status;
typedef struct
{
    ElemType  *elem;
    int length;
    int listsize;
}sqlist;
Status InitList(sqlist *L);
Status DestoryList(sqlist *L);
Status ClearList(sqlist *L);
Status ListEmpty(sqlist L);
int ListLength(sqlist L);
Status GetElem(sqlist L,int i,ElemType *e);
int LocateElem(sqlist L,ElemType e,Status(*compare)(ElemType,ElemType));
Status PriorElem(sqlist L,ElemType cur_e,ElemType *pre_e);
Status NextElem(sqlist L,ElemType cur_e,ElemType *next_e);
Status listInsert(sqlist *L,int i,ElemType e);
Status listDelete(sqlist *L,int i,ElemType *e);
Status listTraverse(sqlist L,Status(*visit)(ElemType *));
Status compare(ElemType a,ElemType b);
Status visit(ElemType *c);
void Union(sqlist *La,sqlist Lb);
void Mergelist(sqlist La,sqlist Lb,sqlist *Lc);
void Mergelist_sq(sqlist La,sqlist Lb,sqlist *Lc);
int main()
{
    int i,j,flag;
    sqlist L,q,c;
    InitList(&q);
    InitList(&L);
    InitList(&c);
    for(i=1;i<10;i++)
        listInsert(&L,i,i);
    for(j=1;j<10;j++)
        listInsert(&q,j,2*j);
    Mergelist_sq(L,q,&c);
    listTraverse(c,visit);
    return 0;
}
Status InitList(sqlist *L)
{
    L->elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    L->length=0;
    L->listsize=LIST_INIT_SIZE;
    return OK;
}
Status DestoryList(sqlist *L)
{
    free(L->elem);
    L->length=0;
    L->listsize=0;
    return OK;
}
Status ClearList(sqlist *L)
{
    L->length=0;
    return OK;
}
Status ListEmpty(sqlist L)
{
    if(L.length)
        return TRUE;
    else
        return FALSE;
}
int ListLength(sqlist L)
{
    return L.length;
}
Status GetElem(sqlist L,int i,ElemType *e)
{
    if(i<1||i>L.length)
        return 0;
    *e=*(L.elem+i-1);
    return OK;
}
int LocateElem(sqlist L,ElemType e,Status(*compare)(ElemType,ElemType))
{
    ElemType *p;
    p=L.elem;
    int i=1;
    while(!compare(*p++,e)&&i<=L.length)
        i++;
    if(i<=L.length)
        return i;
    else
        return FALSE;
}
Status PriorElem(sqlist L,ElemType cur_e,ElemType *pre_e)
{
    int i=2;
    ElemType *p=L.elem++;
    while(i<=L.length && *p!=cur_e)
    {
        i++;
        p++;
    }
    if(i>=L.length)
        return FALSE;
    else
    {
        *pre_e=*--p;
        return OK;
    }
}
Status NextElem(sqlist L,ElemType cur_e,ElemType *next_e)
{
    int i=1;
    ElemType *p=L.elem;
    while(i<=L.length && *p!=cur_e)
    {
        i++;
        p++;
    }
    if(i<=L.length)
    {
        *next_e=*++p;
        return OK;
    }
    else
        return FALSE;
}
Status listInsert(sqlist *L,int i,ElemType e)
{
    ElemType *newbase,*p,*q;
    if(i<1 || i>L->length+1)
        return ERROR;
    if(L->length>=L->listsize)
    {
        newbase=(ElemType *)realloc(L->elem,sizeof(ElemType)*(LISTINCREMENT+LIST_INIT_SIZE));
        if(!newbase)
            exit(OVERFLOW);
        L->elem=newbase;
        L->listsize+=LISTINCREMENT;
    }
    q=L->elem+i-1;
    for(p=L->elem+L->length-1;p>=q;p--)
        *(p+1)=*p;
    *q=e;
    ++L->length;
    return OK;
}
Status listDelete(sqlist *L,int i,ElemType *e)
{
    if(i<1 || i>L->length)
        return ERROR;
    ElemType *p,*q;
    p=L->elem+i-1;
    *e=*p;
    q=L->elem+L->length-1;
    for(++p;p<=q;++p)
        *(p-1)=*p;
    --L->length;
    return OK;
}
Status listTraverse(sqlist L,Status(*visit)(ElemType *))
{
    ElemType *p;
    int i;
    p=L.elem;
    for(i=1;i<=L.length;i++)
        visit(p++);
    return OK;
}
Status compare(ElemType a,ElemType b)
{
    if(a==b)
        return TRUE;
    else
        return FALSE;
}
Status visit(ElemType *c)
{
    printf("%d ",*c);
}
void Union(sqlist *La,sqlist Lb)
{
    int i;
    ElemType e;
    int La_len,Lb_len;
    La_len=ListLength(*La);
    Lb_len=ListLength(Lb);
    for(i=1;i<=Lb_len;i++)
    {
        GetElem(Lb,i,&e);
        if(!LocateElem(*La,e,compare))
            listInsert(La,++La_len,e);
    }
}
void Mergelist(sqlist La,sqlist Lb,sqlist *Lc)
{
    int i=1,j=1,k=0,La_len,Lb_len;
    ElemType ai,bj;
    La_len=ListLength(La);
    Lb_len=ListLength(Lb);
    while((i<=La_len)&&(j<=Lb_len))
    {
        GetElem(La,i,&ai);
        GetElem(Lb,j,&bj);
        if(ai<=bj)
        {
            listInsert(Lc,++k,ai);
            ++i;
        }
        else
        {
            listInsert(Lc,++k,bj);
            ++j;
        }
    }
    while(i<=La_len)
    {
        GetElem(La,i++,&ai);
        listInsert(Lc,++k,ai);
    }
    while(j<=Lb_len)
    {
        GetElem(Lb,j++,&bj);
        listInsert(Lc,++k,bj);
    }
}
void Mergelist_sq(sqlist La,sqlist Lb,sqlist *Lc)
{
    ElemType *pc,*pa=La.elem,*pb=Lb.elem,*pa_last,*pb_last;
    Lc->listsize=Lc->length=La.length+Lb.length;
    pc=Lc->elem=(ElemType *)malloc(sizeof(ElemType)*Lc->listsize);
    if(!Lc->elem)
        exit(OVERFLOW);
    pa_last=La.elem+La.length-1;
    pb_last=Lb.elem+Lb.length-1;
    while(pa<=pa_last&&pb<=pb_last)
    {
        if(*pa<=*pb)
            *pc++=*pa++;
        else
            *pc++=*pb++;
    }
    while(pa<=pa_last) *pc++=*pa++;
    while(pb<=pb_last) *pc++=*pb++;
}


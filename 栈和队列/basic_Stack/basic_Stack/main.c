//
//  main.c
//  basic_Stack
//
//  Created by matthew on 2017/5/11.
//  Copyright © 2017年 matthew. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define  OK  1
#define  ERROR  0
#define  TRUE  1
#define  FALSE  0
#define  INFEASIBLE  -1
#define  OVERFLOW  -2
#define  STACK_INIT_SIZE  100
#define  STACKINCREMENT  10
typedef int Status;
typedef int SElemType;
struct SqStack
{
    SElemType *base;
    SElemType *top;
    int stacksize;
};
typedef struct SqStack SqStack;
Status InitStack(SqStack *S);
Status DestoryStack(SqStack *S);
Status ClearStack(SqStack *S);
Status StackEmpty(SqStack *S);
int StackLength(SqStack *S);
Status GetTop(SqStack *S,SElemType *e);
Status Push(SqStack *S,SElemType e);
Status Pop(SqStack *S,SElemType *e);
Status visit(SElemType c);
Status StackTraverse(SqStack *S,Status (*visit)());
int main()
{
    int i;
    SqStack S;
    //SElemType e;
    InitStack(&S);
    printf("%d ",S.stacksize);
    for(i=3;i<100;i++)
        Push(&S,i);
    StackTraverse(&S,visit);
}
Status InitStack(SqStack *S)
{
    (*S).base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!(*S).base)
        exit(OVERFLOW);
    (*S).top=(*S).base;
    (*S).stacksize=STACK_INIT_SIZE;
    return OK;
}
Status DestoryStack(SqStack *S)
{
    free((*S).base);
    (*S).base=NULL;
    (*S).top=NULL;
    (*S).stacksize=0;
    return OK;
}
Status ClearStack(SqStack *S)
{
    (*S).top=(*S).base;
    return OK;
}
Status StackEmpty(SqStack *S)
{
    if((*S).top==(*S).base)
        return TRUE;
    else
        return FALSE;
}
int StackLength(SqStack *S)
{
    return (*S).top-(*S).base;
}
Status GetTop(SqStack *S,SElemType *e)
{
    if((*S).top>(*S).base)
    {
        *e=*((*S).top-1);
        return OK;
    }
    return ERROR;
}
Status Push(SqStack *S,SElemType e)
{
    if(S->top-S->base>=100)
    {
        (*S).base=(SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
        if(!(*S).base)
            exit(OVERFLOW);
        (*S).top=(*S).base+(*S).stacksize;
        (*S).stacksize+=STACKINCREMENT;
    }
    *((*S).top)++=e;
    return OK;
}
Status Pop(SqStack *S,SElemType *e)
{
    if((*S).top==(*S).base)
        return ERROR;
    *e=*--(*S).top;
    return OK;
}
Status StackTraverse(SqStack *S,Status (*visit)())
{
    while((*S).top>(*S).base)
        visit(*((*S).base++));
    printf("\n");
    return OK;
}
Status visit(SElemType c)
{
    printf("%d ",c);
    return OK;
}

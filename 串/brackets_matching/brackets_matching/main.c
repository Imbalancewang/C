//
//  main.c
//  brackets_matching
//
//  Created by matthew on 2017/5/18.
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
typedef char SElemType;//change the int to char
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
Status StackTraverse(SqStack *S,Status (*visit)(SElemType));
//int judge(SqStack *S,char *str);
int Comp(char e,char c);
void check();
int main()
{
    // SqStack S;
    check();
    // InitStack(&S);
    // Push(&S,'d');
    //printf("%d",StackEmpty(&S));
    return 0;
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
Status StackTraverse(SqStack *S,Status (*visit)(SElemType))
{
    while((*S).top>(*S).base)
        visit(*((*S).base++));
    printf("\n");
    return OK;
}
Status visit(SElemType c)
{
    printf("%c ",c);
    return OK;
}
int Comp(char e,char c)
{
    if(e=='('&&c==')')
        return TRUE;
    else if(e=='['&&c==']')
        return TRUE;
    else if(e=='{'&&c=='}')
        return TRUE;
    else
        return FALSE;
}
void check()
{ // 对于输入的任意一个字符串，检验括号是否配对
    SqStack s;
    SElemType ch[80],*p,e;
    InitStack(&s); // 初始化栈成功
    printf("请输入带括号（()、[]和{}）的表达式\n");
    gets(ch);
    p=ch; // p指向字符串的首字符
    while(*p) // 没到串尾
    {
        switch(*p)
        {
            case '(':
            case '[':
            case '{':Push(&s,*p++); // 左括号入栈，且p++
                break;
            case ')':
            case ']':
            case '}':{if(!StackEmpty(&s)) // 栈不空
            {;
                Pop(&s,&e); // 弹出栈顶元素
                if(!(e=='('&&*p==')'||e=='['&&*p==']'||e=='{'&&*p=='}'))
                { // 出现3种匹配情况之外的情况
                    printf("左右括号不配对\n");
                    exit(ERROR);
                }
            }
            else // 栈空
            {
                printf("缺乏左括号\n");
                exit(ERROR);
            }}
            default: p++;
        } // 其它字符不处理，指针向后移}
    }
    if(StackEmpty(&s)) // 字符串结束时栈空
        printf("括号匹配\n");
    else
        printf("缺乏右括号\n");
}



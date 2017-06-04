//
//  main.c
//  Threaded_BiTree
//
//  Created by matthew on 2017/5/12.
//  Copyright © 2017年 matthew. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  OK  1
#define  FALSE  0
#define  TRUE  1
#define  ERROR  0
#define  OVERFLOW  -2

typedef int Status;
typedef char TElemType;
typedef enum {Link,Thread} PointerTag;
typedef struct BiThrNode{
    TElemType data;
    struct BiThrNode *lchild,*rchild;
    PointerTag LTag,RTag;
}BiThrNode,*BiThrTree;

BiThrTree pre;//glbal varible;

Status CreateBitree(BiThrTree *T);
Status InOrderTraverse_Thr(BiThrTree T,Status(*visit)(TElemType e));
void InThreading(BiThrTree p);
Status InOrderThreading(BiThrTree *Thrt,BiThrTree T);
Status visit(TElemType e);

int main(int argc, const char * argv[]) {
    BiThrTree T,Node;
    CreateBitree(&T);
    InOrderThreading(&T, Node);
    InOrderTraverse_Thr(T, visit);
    return 0;
}
Status CreateBitree(BiThrTree *T){
    TElemType ch;
    scanf("%c",&ch);
    getchar();
    if(ch=='#'){
        *T=NULL;
    }
    else{
        (*T)=(BiThrNode *)malloc(sizeof(BiThrNode));
        if(*T==NULL)
            exit(OVERFLOW);
        else{
            (*T)->data=ch;
            
            CreateBitree(&((*T)->lchild));
            CreateBitree(&((*T)->rchild));
        }
    }
    return OK;
}
Status InOrderTraverse_Thr(BiThrTree T,Status(*visit)(TElemType e)){
    BiThrTree p;
    p=T->lchild;
    while(p!=T){
        while(p->LTag==Link)
            p=p->lchild;
        visit(p->data);
        while(p->RTag==Thread&&p->rchild!=T){
            p=p->rchild;
            visit(p->data);
           // printf("a");
        }
        p=p->rchild;
    }
    return OK;
}
void InThreading(BiThrTree p){
    if(p){
        InThreading(p->lchild);
        if(!p->lchild){
            p->LTag=Thread;
            p->lchild=pre;
        }
        if(!pre->rchild){
            pre->RTag=Thread;
            pre->rchild=p;
        }
        pre=p;
        InThreading(p->rchild);
    }
}
Status InOrderThreading(BiThrTree *Thrt,BiThrTree T){
    (*Thrt)=(BiThrTree )malloc(sizeof(BiThrNode));
    if(!(*Thrt)) exit(OVERFLOW);
    (*Thrt)->LTag=Link;
    (*Thrt)->RTag=Thread;
    (*Thrt)->rchild=(*Thrt);
    if(!(T)) (*Thrt)->lchild=(*Thrt);
    else{
        (*Thrt)->lchild=(T);
        pre=(*Thrt);
        InThreading(T);
        pre->rchild=(*Thrt);
        pre->RTag=Thread;
        (*Thrt)->rchild=pre;
    }
    return OK;
}
Status visit(TElemType e){
    printf("%c",e);
    return OK;
}

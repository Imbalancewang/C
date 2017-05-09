//
//  main.c
//  Tree
//
//  Created by matthew on 2017/5/8.
//  Copyright © 2017年 matthew. All rights reserved.
//
//  偷懒少些了很多函数。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//---------------------------------------//
#define  OK  1
#define  FALSE 0
#define  ERROR 0
#define  TRUE 1
#define  OVERFLOW -2
#define  MaxSize 1000
//---------------------------------------//
typedef  int  Status;
typedef  char TElemType;
typedef  struct  BiTree{
    TElemType data;
    struct BiTree  *lchild, *rchild;
}BiTNode, *BiTree;
//---------------------------------------//
Status InitBiTree(BiTree *T);
Status DestroyBiTree(BiTree *T);
Status CreateBiTree(BiTree *T);
Status BiTreeEmpty(BiTree *T);
Status ClearBiTree(BiTree *T);
int    BiTreeDepth(BiTree *T);
TElemType Root(BiTree *T);
TElemType Value(BiTree p);
void Assign(BiTree p,TElemType value);
Status PreOrderTraverse(BiTree *T);
Status InOrderTraverse(BiTree *T);
Status PostOrderTraverse(BiTree *T);
Status visit(TElemType c);
//---------------------------------------//
int main(int argc, const char * argv[]) {
    
    printf("Hello, World!\n");
    return 0;
}
//---------------------------------------//
Status InitBiTree(BiTree *T){
    *T=NULL;
    return OK;
}
//---------------------------------------//
Status DestroyBiTree(BiTree *T){
    if(*T){
        if((*T)->lchild){
            DestroyBiTree(&(*T)->lchild);
        }
        if((*T)->rchild){
            DestroyBiTree(&(*T)->rchild);
        }
        free(*T);
        *T=NULL;
    }
    return OK;
}
//---------------------------------------//
Status CreateBiTree(BiTree *T){
    TElemType ch;
    scanf("%c",&ch);
    if(ch=='0') return FALSE;
    if(*T)
        exit(OVERFLOW);
    else{
        *T=(BiTree )malloc(sizeof(BiTNode));
        (*T)->data=ch;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
    return OK;
}
//---------------------------------------//
Status BiTreeEmpty(BiTree *T){
    if(*T) return FALSE;
    else  return TRUE;
}
//---------------------------------------//
int BiTreeDepth(BiTree *T){
    int i,j;
    if(!(*T)) return FALSE;
    if((*T)->lchild){
        i=BiTreeDepth(&(*T)->lchild);
    }
    else i=0;
    if((*T)->rchild){
        j=BiTreeDepth(&(*T)->rchild);
    }
    else j=0;
    return i>j?i:j;
}
//---------------------------------------//
TElemType Root(BiTree *T){
    if(*T)
        return (*T)->data;
    else
        return FALSE;
}
//---------------------------------------//
TElemType Value(BiTree p){
    return p->data;
}
//---------------------------------------//
void Assign(BiTree p,TElemType value){
    p->data=value;
}
//---------------------------------------//
Status PreOrderTraverse(BiTree *T){
    if(*T==NULL) return FALSE;
    else{
        printf("%c",(*T)->data);
        PreOrderTraverse(&(*T)->lchild);
        PreOrderTraverse(&(*T)->rchild);
    }
    return OK;
}
//---------------------------------------//
Status InOrderTraverse(BiTree *T){
    if(*T==NULL) return FALSE;
    else{
        PreOrderTraverse(&(*T)->lchild);
        printf("%c",(*T)->data);
        PreOrderTraverse(&(*T)->rchild);
    }
    return OK;
}
//---------------------------------------//
Status PostOrderTraverse(BiTree *T){
    if(*T==NULL) return FALSE;
    else{
        PreOrderTraverse(&(*T)->lchild);
        PreOrderTraverse(&(*T)->rchild);
        printf("%c",(*T)->data);
    }
    return OK;
}
//---------------------------------------//
Status visit(TElemType c){
    printf("%c ",c);
    return OK;
}

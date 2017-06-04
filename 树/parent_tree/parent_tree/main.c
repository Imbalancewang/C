//
//  main.c
//  family_tree
//
//  Created by matthew on 2017/5/24.
//  Copyright © 2017年 matthew. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define  MAX_TREE_SIZE 100
#define  OK  1
#define  ERROR  0
#define  TRUE  1
#define  FALSE  0
#define  OVERFLOW -2
typedef char TElemType;
typedef int  Status;
typedef struct PTNode{
    TElemType data;
    int parent;
}PTNode;
typedef struct {
    PTNode nodes[MAX_TREE_SIZE];
    int r,n;
}PTree;

Status InitBiTree(PTree T);
int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

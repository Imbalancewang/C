//
//  main.c
//  basic_string
//
//  Created by matthew on 2017/5/12.
//  Copyright © 2017年 matthew. All rights reserved.
//

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define  OK  1
#define  FALSE  0
#define  TRUE  1
#define  ERROR  0
#define  INFEASIBLE  -1
#define  OVERFLOW  -2
#define  MAXSIZE  1024
typedef int Status;
typedef char sstring[MAXSIZE];
Status StrAssign(sstring *T,char *chars);
Status StrCopy(sstring *T,sstring *S);
Status StrEmpty(sstring *S);
Status StrCompare(sstring *T,sstring *S);
int StrLength(sstring *S);
Status ClearString(sstring *S);
Status Concat(sstring *T,sstring *S1,sstring *S2);
Status SubString(sstring *Sub,sstring *S,int pos,int len);
Status Index(sstring *S,sstring *T,int pos);
Status Replace(sstring *S,sstring *T,sstring *V);
Status StrInsert(sstring *S,int pos,sstring *T);
Status StrDelete(sstring *S,int pos,int len);
Status DestroyString(sstring *S);
int main()
{
    sstring S,T;
    StrAssign(&S,"abcdefghijk");
    StrAssign(&T,"jk");
    //StrAssign(&V,"ppppp");
    //Replace(&S,&T,&V);
    printf("%s",S);
}
Status StrAssign(sstring *T,char *chars)
{
    int i;
    for(i=0;*chars!='\0';i++,chars++)
    {
        (*T)[i]=*chars;
    }
    (*T)[i]='\0';
    return OK;
}
Status StrCopy(sstring *T,sstring *S)
{
    int i;
    for(i=0;(*T)[i]!='\0';i++)
    {
        (*S)[i]=(*T)[i];
    }
    return OK;
}
Status StrEmpty(sstring *S)
{
    return (*S)[0]=='\0'?1:0;
}
Status StrCompare(sstring *T,sstring *S)
{
    int i,lent,lens;
    for(i=0;(*T)[i]!='\0'&&(*S)[i]!='\0';i++)
    {
        if((*T)[i]>(*S)[i])
            return OK;
        else if((*T)[i]<(*S)[i])
            return ERROR;
        else
            continue;
    }
    lent=strlen(*T);
    lens=strlen(*S);
    if(lent==lens)
        return FALSE;
    else if(lent>lens)
        return TRUE;
    else
        return FALSE;
}
int StrLength(sstring *S)
{
    int len=0,i;
    for(i=0;(*S)[i]!='\0';i++)
    {
        len++;
    }
    return len;
}
Status ClearString(sstring *S)
{
    (*S)[0]='\0';
    return OK;
}
Status Concat(sstring *T,sstring *S1,sstring *S2)
{
    int i,j;
    int len1,len2;
    len1=strlen(*S1);
    len2=strlen(*S2);
    if(len1+len2<1024)
    {
        for(i=0;(*S1)[i]!='\0';i++)
            (*T)[i]=(*S1)[i];
        for(j=0;(*S2)[j]!='\0';j++)
            (*T)[i++]=(*S2)[j];
        (*T)[i]='\0';
    }
    else if(len1>=1024)
    {
        for(i=0;i<1024;i++)
            (*T)[i]=(*S1)[i];
    }
    else if(len1<1024&&len1+len2>=1024)
    {
        for(i=0;(*S1)[i]!='\0';i++)
        {
            (*T)[i]=(*S1)[i];
        }
        for(j=0;(*S2)!='\0';j++)
        {
            (*T)[i++]=(*S2)[j];
        }
    }
    return OK;
}
Status Index(sstring *S,sstring *T,int pos)
{
    int n,m,i=pos;
    sstring Sub;
    n=strlen(*S);m=strlen(*T);
    if(pos>0)
    {
        while(i<=n-m+1)
        {
            SubString(&Sub,S,i,m);
            if(StrCompare(&Sub,T)!=0)
                ++i;
            else
                return i;
        }
    }
    return OK;
}
Status DestroyString(sstring *S)
{
    //no use???????????????????
    free(S);
    return OK;
}
Status StrDelete(sstring *S,int pos,int len)
{
    int i=0,lens,j,k,m,n;
    lens=strlen(*S);
    if(pos>=0&&pos<=lens)
    {
        while(i<=len)
        {
            for(j=pos;j<=lens;j++)
            {
                (*S)[j]=(*S)[j+1];
            }
            i++;
        }
        return OK;
    }
    return FALSE;
}
Status Replace(sstring *S,sstring *T,sstring *V)
{
    int i=0,j=0,m=strlen(*T),n=strlen(*V);
    for(i=0;(*S)[i]!='\0';i++)
    {
        j=Index(S,T,i);
        if(j>0)
        {
            StrDelete(S,j,m);
            StrInsert(S,j,V);
        }
    }
    return OK;
}
Status StrInsert(sstring *S,int pos,sstring *T)
{
    int lens,lent,i,j,k;
    sstring temp;
    lens=strlen(*S);lent=strlen(*T);
    if(pos>=0&&pos<=lens&&lens+lent<=1024)
    {
        for(i=0;i<pos;i++)
        {
            temp[i]=(*S)[i];
            k=i;
        }
        for(j=0;(*T)[j]!='\0';j++)
        {
            temp[i++]=(*T)[j];
        }
        for(k=k+1;(*S)[k]!='\0';k++)
        {
            temp[i++]=(*S)[k];
        }
        temp[i]='\0';
        for(i=0;temp[i]!='\0';i++)
            (*S)[i]=temp[i];
        //  (*S)[i]='\0';
        return OK;
    }
    return FALSE;
}
Status SubString(sstring *Sub,sstring *S,int pos,int len)
{
    int i,j;
    for(i=pos,j=0;i<pos+len;i++)
        (*Sub)[j++]=(*S)[i];
    (*Sub)[j]='\0';
    return OK;
}

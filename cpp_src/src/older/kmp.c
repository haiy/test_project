#include<stdio.h>
#include<stdlib.h>
/*
 * KMP算法的理解可以分为俩个步骤，首先是跳越移动，
 * 然后是怎么跳的问题。
 * */
int main()
{
    int len1;
    scanf("%d",&len1);
    /*这个是主字符串*/
    char *input=(char *)malloc(sizeof(char)*len1);
    scanf("%s",input);
    int len2;
    scanf("%d",&len2);
    /*这个是要查找的模式字符串*/
    char *a=(char *)malloc(sizeof(char)*len2);
    scanf("%s",a);
    /*存储模式字符串中每个字符的跳跃位置*/
    int *n=(int *)malloc(sizeof(int)*len2);
    n[1]=0;
    /*当第j个元素不等的时候，就比较第n[k]个元素的情况*/
    int i=1;
    int j=0;
    n[1]=0;
    while(i<len2)
    {
        if(a[i]==a[j]||j==0)
        {
            ++i;
            ++j;
            n[i]=j;
            printf("n[%d]:%d\n",i,j);
        }
        else
        {
            j=n[j];
//            printf("What's the matter?!");
        }
    }
    for(i=0;i<len1;i++)
    {
        for(j=0;j<len2;j++)
        {
            if(a[j]!=input[i])
            {
                j=n[j];
            }
            if(j==0)
            {
                break;
            }
        }
        if(j==len2)
        {
            puts("StringMatch!");
            break;
        }
    }
    if(i==len1&&j<len2)
    {
        puts("String Not Found!");
    }

}

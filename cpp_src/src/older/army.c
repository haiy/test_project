/*
 * Author:haiy
 * Date:Aug 21 2013
 * Description:http://ds.fzu.edu.cn/Uploads/Problem/army.pdf
 * */

#include<stdio.h>
#include<stdlib.h>

typedef struct legion
{
    int num;
    struct legion * pn;
}Legio,*Legio_ptr;

void merge_army(Legio_ptr * army,int *rec,int a,int b)
{
    a=a-1;
    b=b-1;
    Legio_ptr cur=army[a];
    while(cur->pn)
    {
        cur=cur->pn;
    }
    cur->pn=army[b];
    army[b]=NULL;
    rec[a]+=rec[b];
    rec[b]=0;
}
void insert_army(Legio_ptr *army,int *rec,int a,int x)
{
    a=a-1;
    Legio_ptr new_a=(Legio_ptr)malloc(sizeof(Legio));
    new_a->num=x;
    new_a->pn=army[a];
    army[a]=new_a;
}
void delete_army(Legio_ptr *army,int *rec,int a, int x)
{
    a=a-1;
    Legio_ptr cur=army[a];
    if(cur->num==x)
    {
        army[a]=cur->pn;
        free(cur);
    }
    while(cur->pn)
    {
        if(cur->pn->num!=x)
        {
            cur=cur->pn;
        }
        else
        {
            Legio_ptr tp=cur->pn;
            cur->pn=cur->pn->pn;
            free(tp);
        }
    }
}
void query_army(Legio_ptr *army,int *rec,int a)
{
    a=a-1;
    Legio_ptr cur=army[a];
    if(cur==NULL)
    {
        puts("-1");
    }
    else
    {
        printf("%d",cur->num);
        while(cur->pn)
        {

            printf(" %d",cur->pn->num);
            cur=cur->pn;
        }
        printf("\n");
    }

}

void main()
{
    int N,M;
    scanf("%d%d",&N,&M);
    while( !(N>=2&&M<=1000) )
    {
        puts("Error input,N>=2,M<=1000,Again:");
        scanf("%d%d",&N,&M);
    }
    int i;
    int *rec=(int*)malloc(sizeof(int)*N);//每个地区军队数
    Legio_ptr *army=(Legio_ptr *)malloc(sizeof(Legio_ptr)*N);//每个地区头结点指针
    for(i=0;i<N;i++)
    {
        scanf("%d",rec+i);//当前地区的军队个数
        army[i]=(Legio_ptr)malloc(sizeof(Legio));
        Legio_ptr cur=army[i];
        scanf("%d",&cur->num );
        int j;
        /*如何分配连续分配链表节点*/
        for(j=1;j<rec[i];j++)
        {
            cur->pn=(Legio_ptr)malloc(sizeof(Legio));
            scanf("%d",&cur->pn->num);//当前军队的人数
            cur=cur->pn;
            cur->pn=NULL;
        }
    }
    int j; 
    for(j=0;j<M;j++)
    {
        char c;
        int a,b,x;
        /* 
         * ！！！ 注意这个地方的 空格+c%，主要目的是方便
         * 直接终端导入测试文件了！
         * */
        scanf(" %c",&c);
        switch ( c )
        {
            case 'U':
                scanf("%d%d",&a,&b);
                merge_army(army,rec,a,b);
                break;
            case 'I':
                scanf("%d%d",&a,&x);
                insert_army(army,rec,a,x);
                break;
            case 'D':
                scanf("%d%d",&a,&x);
                delete_army(army,rec,a,x);
                break;
            case 'Q':
                scanf("%d",&a);
                query_army(army,rec,a);
                break;
            default:
                break;
        }
    }
}


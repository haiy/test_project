/*
 * Author:haiy
 * Date:Aug 28 2013
 * Description:http://ds.fzu.edu.cn/Uploads/Problem/War.pdf
 * */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>

typedef struct Node
{
    int val;
    struct Node *prev;
}node,*node_ptr;

typedef struct Stack
{
    node_ptr top;
    node_ptr bottom;
}stack,*stack_ptr;

void push_node(stack_ptr s,int x)
{
    node_ptr new_node=(node_ptr)malloc(sizeof(node));
    new_node->prev=NULL;
    new_node->val=x;
    if(s->top==NULL)
    {
        s->top=new_node;
        s->bottom=new_node;
    }
    else
    {
        new_node->prev=s->top;
        s->top=new_node;
    }
}

int pop_node(stack_ptr s)
{
    if(s->top)
    {
        node_ptr cur=s->top;
        int x=s->top->val;
        s->top=s->top->prev;
        free(cur);
        cur=NULL;
        return x;
    }
    else
    {
        return -1;
    }
}

/* 素数检测，是则返回1，不是返回0 */
int prime_check(int in)
{
    int i;
    if(in==2||in==3)
    {
        return 1;
    }
    for(i=2;i<=in/2;i++)
    {
        if(in%i==0)
        {
            return 0;
        }
    }
    return 1;
}

/* 找到当前的最短路径值,返回其线性位置 */
int find_MIN(int *D,int *D_status,int N,int M)
{
    int min=INT_MAX;
    int pos=0;
    int i;
    for(i=0;i<N*M;i++)
    {
        if(D[i]<=min&&(D_status[i]!=-1))
        {
            min=D[i];
            pos=i;
        }
    }
    return pos;
}

/* 计算a和b点之间的距离，如果是相邻点，那么距离为1，否则都为最大值 */
int dst_cal(int a,int b, int N, int M)
{
    if(a/M==b/M && abs(a-b)==1)
    {
        return 1;
    }
    if( abs(a/M-b/M)==1 && a%M==b%M)
    {
        return 1;
    }
    return INT_MAX;
}

void print_map(int *D,int N,int M)
{
    int i;
    for(i=0;i<N*M;i++)
    {
        if(i%M==0)
        {
            //printf("\n");
        }
        //printf("%-10d\t",D[i]);
    }
    //printf("\n");
}

int dijkstra(int *D,int *p,int *D_status,int N,int M,int start,int end)
{
    int i;
    int k;
    for(i=1;i<N*M-1;i++)
    {
        //puts("p check !!");
        print_map(p,N,M);
        int j=find_MIN(D,D_status,N,M);
        //printf("current min:%d(%d,%d)\n",j,j/M,j%M);
        print_map(D,N,M);
        if(j==end)
        {
            //printf("Now previous node :p[%d]:%d",j,p[j]);
            return p[j];
        }
        D_status[j]=-1;

        for(k=0;k<N*M;k++)
        {
            if(D_status[k]!=-1)
            {
                /*
                 * 找出添加了当前最短的点之后能否缩短
                 * 起始点到当前点的距离
                 * */
                if((D[j]+dst_cal(j,k,N,M))<D[k]&&dst_cal(j,k,N,M)!=INT_MAX)
                {//该等式成立说明该点对当前节点有用
                    D[k]=D[j]+dst_cal(j,k,N,M);
                    p[k]=j;
                    //printf("add node :p[%d]:%d\n",k,j);
                }
            }
        }
        //puts("After being updated:");
        print_map(D,N,M);
    }
    return -1;
}



int main()
{
    int N,M;
    scanf("%d%d",&N,&M);
    //printf("N,%d,M，%d\n",N,M);
    int i;
    int j;
    int start;
    int end;
    /* shortest path length */
    int *D=(int *)malloc(sizeof(int)*N*M);
    for(i=0;i<N*M;i++)
    {

        D[i]=INT_MAX;
        D[i]=1;
    }

    /* 用-1表示该点不在D中 */
//    //puts("Begin to read in data:");
    int ival;
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            scanf("%d",&ival);
//            //printf("(%d,%d):%d\n",i,j,ival);
            if(ival==0)
            {
                start=i*M+j;
            }
            else if(ival==1)
            {
                end=i*M+j;
            }
            else
                if(prime_check(ival)==1)
                {
                    D[i*M+j]=-1;
//                    //printf(" D[%d]:%d is prime \n",i*N+j,D[i*N+j]);
                }
                else
                {
                    D[i*M+j]=INT_MAX;
//                    //printf("D[%d]:%d none pime\n",i*N+j,D[i*N+j]);
                }
        }
//        //printf("\n");
    }
//    print_map(D,N,M);
    //printf("start:(%d,%d),end:(%d,%d)\n",start/M,start%M,end/M,end%M);
    //puts("Data read finished!");
    D[start]=-1;
    D[end]=INT_MAX;

    print_map(D,N,M);
    //puts("D initialized!");
    stack s;
    s.top=s.bottom=NULL;
    push_node(&s,end);
    /* D_status 中存放当前点是否找到了最短路径，
     * 对应的D中存放着到当前点的最短路径长度*/
    int *D_status=(int *)malloc(sizeof(int)*N*M);
    /* p中存放对应于每个点的最短路径的上一个点 */
    int *p=(int *)malloc(sizeof(int)*N*M);
    for(i=0;i<N*M;i++)
    {//初始化下，如果是一个孤立的点，那么它的p值
        //肯定是-1，以此来跳出下面的路径循环
        p[i]=-1;
    }
    D[start]=0;
    p[start]=start;
    int k=0;
    /* 必须先初始化从起点到其他所有点的情况 */
    for(k=0;k<N*M;k++)
    {
        if(D_status[k]!=-1)
        {
            if((D[start]+dst_cal(start,k,N,M))<D[k]&&dst_cal(start,k,N,M)!=INT_MAX)
            {//该等式成立说明该点对当前节点有用
                D[k]=D[start]+dst_cal(start,k,N,M);
                p[k]=start;
                //printf("Initialize p[%d]:%d\n",k,p[k]);
            }
        }
    }
    /* 倒序查找最短路径的,
     * 首先找到能达到目的地的最短
     * 路径的上一个节点，然后找到
     * 能达到上一个节点的最短路径
     * 的再上一个节点。
     * */
    while(start!=end)
    {
        for(i=0;i<N*M;i++)
        {
            D_status[i]=D[i];
        }
        //printf("start(%d,%d),end(%d,%d)\n",start/M,start%M,end/M,end%M);
        end=dijkstra(D,p,D_status,N,M,start,end);
        //printf("return end %d(%d,%d)\n",end,end/M,end%M);
        if(end==-1)
        {
            puts("What a pity!");
            break;
        }
        push_node(&s,end);
    }
    node_ptr cur=s.top;
    int step=0;
    while(cur)
    {
        step+=1;
        printf("(%d,%d)",cur->val/M,cur->val%M);
        pop_node(&s);
        cur=cur->prev;
    }
    free(D);
    free(D_status);
    printf("\n");
    printf("%d\n",step-1);
    return 0;
}

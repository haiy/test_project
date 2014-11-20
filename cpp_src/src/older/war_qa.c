/*
 * Author:haiy
 * Date:Aug 29 2013
 * Description:http://ds.fzu.edu.cn/Uploads/Problem/War.pdf
 * */
#include<stdio.h>
#include<stdlib.h>

typedef struct Army
{
    int class_num;
    int solider;
    struct Army * rear;
}class,*class_ptr;

void check_army(class_ptr a)
{
    class_ptr cur=a->rear;
    while(cur)
    {
        printf("(%d,%d),",cur->class_num,cur->solider);
        cur=cur->rear;
    }
    printf("\n");
}

int query_insert_class(class_ptr a,int sol,int cln)
{
    class_ptr cur=a;
    class_ptr n=(class_ptr)malloc(sizeof(class));
    n->rear=NULL;
    n->class_num=cln;
    n->solider=sol;
    /* leave out the fist node */
    if(cur->rear==NULL)
    {
        a->rear=n;
        return 1;
    }
    cur=cur->rear;
    while(cur)
    {
        if(cur->rear==NULL)
        {
            cur->rear=n;
            //puts("1");
            //check_army(a);
            return 1;
        }
        else if(cur->class_num==n->class_num&&
                cur->rear->class_num!=n->class_num)
        {
            n->rear=cur->rear;
            cur->rear=n;
            //puts("2");
            //check_army(a);
            return 1;
        }
        cur=cur->rear;
    }

    return 1;
}

int main()
{
    class_ptr army=(class_ptr)malloc(sizeof(class));
    army->rear=NULL;
    char *input=(char *)malloc(sizeof(char)*4);
    scanf("%s",input);
    //printf("%s,%d\n",input,strcmp("PUSH","PUSH"));
    while(strcmp(input,"PUSH")==0)
    {
        int c;
        int s;
        scanf("%d%d",&s,&c);
        //printf("c:%d,s:%d,cl:%s\n",c,s,input);
        query_insert_class(army,s,c);
        scanf("%s",input);
        //printf("c:%d,s:%d,cl:%s\n",c,s,input);
    }
    class_ptr cur=army->rear;
    printf("%d",cur->solider);
    while(cur->rear)
    {
        printf(" %d",cur->rear->solider);
        cur=cur->rear;
    }
    printf("\n");
    return 0;
}

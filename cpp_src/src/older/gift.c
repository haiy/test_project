/*
 * Author:haiy
 * Date:Aug 26 2013
 * Description:http://ds.fzu.edu.cn/Uploads/Problem/gift.pdf
 * */
#include<stdio.h>
#include<stdlib.h>

typedef struct StackNoe{
    char val;
    struct StackNoe * lower;
}sn,*sn_ptr;

void check_stack(sn_ptr top)
{
    sn_ptr cur=top;
    while(cur)
    {
        printf("%c",cur->val);
        cur=cur->lower;
    }
    printf("\n");
}

void push_stack(sn_ptr *top,char val)
{
    sn_ptr tp=(sn_ptr)malloc(sizeof(sn));
    tp->val=val;
    tp->lower=*top;
//  puts("Before");
//  check_stack(*top);
    *top=tp;
    //puts("After");
    //check_stack(*top);
}
void pop_stack(sn_ptr * top)
{
    sn_ptr tp=*top;
    *top=(*top)->lower;
    free(tp);
    tp=NULL;
}
void brk_stack(sn_ptr *top)
{
    while((*top)->lower)
    {
        pop_stack(top);
    }
}

int main()
{
    sn_ptr top=(sn_ptr)malloc(sizeof(sn));
    sn_ptr bottom=top;
    top->lower=NULL;
    char cur;
    scanf("%c",&cur);

    int N=0; //总的需要拆开的包装数
    int n=0; //拆开当前礼物所需包装数
    while(cur!='\n' && cur!='\0')
    {
        if( cur=='(' )
        {
            //开始拆当前包装就+1
            n+=1;
            push_stack(&top,cur);
        }
        else if ( cur== 'G' )
        {//拆到礼物就把当前已拆包装数累加
            N+=n;
            //重置当前拆开包装数
            n=0;
        }
        else if ( cur == ')' )
        {
            //拆完一个包装就减去一个，
            //避免空包装捣乱
            pop_stack(&top);
            n-=1;
            //如果是空包装了就减去
            if(n<0)
            {
                n=0;
            }
        }
        scanf("%c",&cur);
    }
    printf("%d\n",N);
    brk_stack(&top);
    free(top);
    return 0;
}

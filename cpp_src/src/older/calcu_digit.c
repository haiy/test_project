/*
 * Author:haiy
 * Date:Aug 20 2013
 * Description: http://ds.fzu.edu.cn/Uploads/Problem/calcu.pdf
 * calculate the n!-m! ,while even 21! will overflow, here
 * (0<=n<=m<=100);
 * */

#include<stdio.h>
#include<stdlib.h>

/* structure of one bit list node */
typedef struct digit{
    /* value of current bit */
    int val;
    /* pointer to the higher bit */
    struct digit * high;
    struct digit *low;
}bit,*bit_ptr;

/*
 * calculate a list digit mutilpies a number range
 *  from 0 to 10.
 *  ����һ�������ʾ�����ݺ�һ��������10�������Ļ�
 *  Ϊʲô��������Ϊ�߾�����������Ĺ�����λ����
 *  ��̬�仯��
 * */
bit_ptr cal_large(bit_ptr *last_bit, int m)
{
    bit_ptr cur=*last_bit;
    int carry=0;
    /*
     * ÿλ�ϵ��������ϱ����������ϵ�һλ�Ľ�λ��
     * �õ���ǰλ�Ľ�λ������ֵ��
     * */
    while(cur)
    {
        cur->val*=m;
        cur->val+=carry;
        carry=cur->val/10;
        cur->val=cur->val%10;
        if(cur->high)
        {
            cur=cur->high;
        }
        else
            break;
    }
    /*
     * ������Ϊ���н�λ������ô�ͷ���һ���µ���
     * ��λ
     * */
    printf("carry:%d\n",carry);
    while(carry>0)
    {
        cur->high=(bit_ptr)malloc(sizeof(bit));
        cur->high->low=cur;
        cur->high->high=NULL;

        cur->high->val=carry%10;
        carry=carry/10;
        cur=cur->high;
    }
    return cur;
}
bit_ptr minus_list(bit_ptr *last_bit,int m)
{
    int flag=1;
    bit_ptr cur=*last_bit;
    while(m/10>0&&cur)
    {
        cur->val-=m%10;
        if(cur->val<0)
        {
            if(cur->high)
            {
                cur->val+=10;
                cur->high->val-=1;
                if(cur->high->val)
                {
                    free(cur->high);
                    cur->high=NULL;
                }
            }
            else
            {
                flag=-1;
                break;
            }
        }
        m=m/10;
        cur=cur->high;
    }
    if(m/10>0)
    {//��ҪĿ���ǽ�����λ��ȫ�������У�
        //��m/10��=0ʱ����һ�����λ
        while(m/10>0)
        {
            cur->high=(bit_ptr)malloc(sizeof(bit));
            cur->high->low=cur;
            cur->high->high=NULL;
            cur->high->val=m%10;
            m=m/10;
        }
        flag=-1;
    }
    if(m/10==0)
    {
        if(cur)
        {
            cur->val-=m;
        }
}

void main()
{
    bit_ptr l=(bit_ptr)malloc(sizeof(bit));
    bit_ptr cur;
    l->high=NULL;
    l->low=NULL;
    l->val=24;
    cur=cal_large(&l,25);
    cur=cal_large(&l,25);
    while(cur)
    {
        printf("%d",cur->val);
        cur=cur->low;
    }
    printf("\n");
}

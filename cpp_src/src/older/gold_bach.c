/*
 * 作者：haiy
 * 邮箱：haiyangfu512@gmail.com
 * 说明：程序要求来源，http://ds.fzu.edu.cn/Uploads/Problem/goldbach.pdf
 *      主要是验证哥德巴赫猜想。
 * 日期：7月25
 *
 * 方法1，是直接对每个数是否是质数进行判断
 * 方法2，将所有非质数都标记下来
 * 方法2，比较好。
 * 为什么呢？质数是规律性比较小部分，而非质数是规律性比较大的部分，
 * 所以将规律性大的都剔除之后则自然剩下的都是特殊的
 * */

#include<stdlib.h>
#include<string.h>
#include<stdio.h>


/*检查N是否是质数*/
char prime_check(int N)
{
    int i=0;
    for(i=2;i<N;i++)
    {
        if(N%i==0)
        {
            return '0';
        }
    }
    return '1';
}
/* 方法1，找出所有小于R的质数, 直接除
 * */
char * lower_prime(int R)
{
    /*用一个0，1字符串来表示对应位置的数值是不是
     * 素数
     */
    char *res=(char *)malloc(sizeof(char)*R);
    memset(res,'0',R);
    int i=0;
    int count=0;
    for(i=2;i<R;i++)
    {
        res[i]=prime_check(i);
        if(res[i]=='1')
        {
            count+=1;
        }
    }
    int *prime_array=(int *)malloc(sizeof(int)*count);
    count=0;
    for(i=2;i<R;i++)
    {
        if(res[i]=='1')
        {
            prime_array[count]=i;
        }
    }
    return res;
}

/*方法2，筛选法*/
char *lower_prime_1(int R)
{
    char *res=(char *)malloc(sizeof(char)*R);
    memset(res,'1',R);
    res[0]=res[1]='0';res[2]='1';
    int i=2;
    for(i=2;i<R/2;i++)
    {
        int X=2;
        while(i*X<R)
        {
            res[i*X]='0';
            X+=1;
        }
    }
    return res;
}


/*计算得到的素数集合中有几组两两
 * 相加的和等于输入的范围数R在这
 * 我主要采用顺序相加计算的方法。
 * 也就是说，其实每个数都是用其
 * 数组中的下标代表其值，然后数组
 * 中存放的是标志1或者0，只要给出
 * 一个数的位置就能判断其能不能
 * 和其他的数的和等于R。
 * 比如说R=11，在res[5]='1',那么5
 * 是小于11的素数，若要5+x=11，那
 * 么x=6，这时候看res[6]=0，不是
 * 素数，所以5不满足。也就是说没有
 * 数小于11的素数和5的和等于11. 
 */
int sum_count(char *res,int R)
{
    int i=2;
    int count=0;
    for(i=2;i<=R/2;i++)
    {
        if(res[i]=='1'&&res[R-i]=='1')
        {
            count+=1;
        }
    }
    return count;
}

/*方法2，*/
int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        printf("Parameter Error! Find  %d arguments\n",argc);
        exit(0);
    }
    printf("arg1:%s\targ2:%s\n",argv[0],argv[1]);
    int R=atoi(argv[1]);
    /*改变lower_prime采用不同的计算策略*/
    char *res=lower_prime_1(R);
    int i=2;
    for(i=2;i<atoi(argv[1]);i++)
    {
	    if(res[i]=='1')
        {
            printf("%d\t",i);
        }
    }
    printf("\n");

    printf("There are %d pairs satified.\n",sum_count(res,R));

    return 0;
}

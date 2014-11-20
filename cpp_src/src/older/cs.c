/*Date:2013/July/24
 * Author:haiy
 * Qustion From:http://ds.fzu.edu.cn/Uploads/Problem/sum.pdf
1.
1+2=3
2+3=5
3+4=7
4+5=9

2.
1+2+3=6
2+3+4=9
3+4+5=10
4+5+6=11

3.
1+2+3+4=10
2+3+4+5=14
3+4+5+6=18
4+5+6+7=22

有什么规律呢？
目的是找谁和谁的规律？

问题是要找一个数能表示成连续数和的表示方法，再推理下要找的是如何将一个数表示成连续数，
更进一步，如何将一个数表示成两个连续数或者三个连续数的和，也就是说，要找的规律有俩个，
一个是表示成几个连续数，另外一个是表示成哪几个连续数。

那么一个数能表示成两个连续数的和有什么特点呢？
表示成三个连续数有什么特点？

连续数与连续数之间有什么特点呢？连续数与连续数之间的关系决定了特定的连续数是由哪几个连续数
组成的。

进一步就可以发现，所有等个数的连续数的和是等差的。最小值都是最初值，那么也就是说在确定了第一个
连续数的和之后，后面的都可以推导出来咯！！哈哈~~
问题解决！

那么再进一步思考下就可以知道，判断一个数能不能分成N个连续数，
首先这个数减去N的从1到N的和，然后看这个数能不能整除N，如果可以分成
N个连续数之和。

前N个数的和，如果是N偶数，那么sum(1,N)=（N+1）N/2，如果为奇数，Sum（1，N）=（N+1）*（N-1）/2+（N+1）/2=N*（N-1）/2

sum=N*(N-1)/2,  N*(N+1)/2
 *解题思路：
 *
 * */


#include<stdio.h>
#include<stdlib.h>

/*前N个正整数的和*/
int sum(int split)
{
        if(split%2==0)
        {
                return (split+1)*split/2;
        }
        else
        {
                return (split-1)*split/2;
        }
}

/*计算输入的Input能够分割成几个连续整数和*/
int cons_seq(int input)
{
        int i=0;
        int count=0;
        for(i=2;sum(i)<=input;i++)
        {
                if( (input-sum(i))%i==0 )
                {
                        count+=1;
                }
        }
        return count;
}

int main(int argc,char *argv[])
{
        if(argc!=2)
        {
                printf("Parameter error! %d input\n.",argc);
                printf("%s\n",argv[0]);
                exit(1);
        }
        printf( "%d\n",cons_seq( atoi(argv[1]) ) );
}

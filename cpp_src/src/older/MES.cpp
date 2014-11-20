#include<stdio.h>
#include<stdlib.h>
#include<math.h>
/*
Author:haiyfu
Date:July 24
Notes:
输入一个整数a,
输出一个数组b，b中的每个元素是都是a中对应位置元素
除了自身的积。
例如输入整数 123，那么输出的数组中的元素应该为
b[0]=2*3,b[1]=1*3,b[2]=1*2;

题目参考Evernote 的InterviewStreet。

*/

void product(int *input,int *output,int size)
{
	int i=0;
	int prt=1;
	/*算法思路：先算所有项的积，然后
	除以对应位置的值，即可得到对应位置的
	结果*/
	for(i=0;i<size;i++)
	{
		if(input[i]!=0)
		{
			prt=prt*input[i];
		}
		output[i]=input[i];
		printf("opt->[%d]\n",output[i]);
	}
	printf("prt->[%d]\n",prt);
	for(i=0;i<size;i++)
	{
		if(output[i]!=0)
		{
			output[i]=prt/output[i];
		}
		else
		{
			output[i]=0;
		}
		printf("Output[%d]:%d\n",i,output[i]);
	}
}
/*
先将输入的整数转换成一个数组，倒序。
根据最高为的值肯定属于1-9作取余判断的终止标准
先算整体的数值的位数，比如123是三位数，100，也是
三位数
*/
int * data_input(int input,int *len)
{
	int i=0;
	input=abs(input);
	int tp=input;
	while(( (float)tp )/10>=1)
	{
		tp=tp/10;
		i++;
	}
	int *res=(int *)malloc(sizeof(int)*(i+1));
	*len=i+1;
	i=0;
	while(( (float)input )/10 >=1)
	{
		res[i]=input%10;
		input=input/10;
		printf("i %d res->%d\tinput:%d\n",i,res[i],input);
		i++;
	}
	res[i]=input%10;
	printf("res->%d\tinput:%d\n",res[i],input);

	return res;
}
int data_output(int * output,int size)
{
	int i=0;
	int optint=0;
	for(i=0;i<size;i++)
	{
		optint=optint+output[i]*pow(10.0,i);
	}
	return optint;
}

/*main需要另外调整*/
int main(char argc,char *argv[])
{
	int len;
	int *res=data_input(10230023,&len);
	int i=0;
	printf("len:%d\n",len);
	for(i=0;i<len;i++)
	{
		printf("%d now %d\n",i,res[i]);
	}
	getchar();
	int *output=(int *)malloc(sizeof(int)*len);
	product(res,output,len);
	int fn=data_output(output,len);
	printf("%d\n",fn);
	free(res);
	free(output);
	getchar();
}
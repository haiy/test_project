#include<stdio.h>
#include<stdlib.h>
#include<math.h>
/*
Author:haiyfu
Date:July 24
Notes:
����һ������a,
���һ������b��b�е�ÿ��Ԫ���Ƕ���a�ж�Ӧλ��Ԫ��
��������Ļ���
������������ 123����ô����������е�Ԫ��Ӧ��Ϊ
b[0]=2*3,b[1]=1*3,b[2]=1*2;

��Ŀ�ο�Evernote ��InterviewStreet��

*/

void product(int *input,int *output,int size)
{
	int i=0;
	int prt=1;
	/*�㷨˼·������������Ļ���Ȼ��
	���Զ�Ӧλ�õ�ֵ�����ɵõ���Ӧλ�õ�
	���*/
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
�Ƚ����������ת����һ�����飬����
�������Ϊ��ֵ�϶�����1-9��ȡ���жϵ���ֹ��׼
�����������ֵ��λ��������123����λ����100��Ҳ��
��λ��
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

/*main��Ҫ�������*/
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
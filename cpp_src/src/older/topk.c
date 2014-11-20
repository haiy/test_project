/*
 * 作者：haiy
 * 日期：July 28 2013 Morning
 * */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define MAX(a,b) (a)>(b)?(a):(b)
#define MIN(a,b) (a)>(b)?(b):(a)
void prinpt(int *input,int len)
{
	int i;
	for(i=0;i<len;i++)
	{
		printf("intput:%d\t",*(input+i));
	}
	printf("\n");
}
/*
 * 冒泡排序
 * 通过len-1趟的比较找到每个排序位置上的元素
 * 第一次找到最大的元素，第二次找到第二大的
 * 元素，依次找到每个位置的元素，第一次需要
 * 比较len，第二次需要len-1个元素，……，最
 * 后需要比较的次数为len个数的累加和，其时间
 * 复杂度为n^2.
 * */
void bub_sort(int *input,int len)
{
	int i=0;
	int j=0;
	for(i=0;i<len;i++)
	{
		for(j=i;j<len;j++)
		{
			if(input[i]>input[j])
			{
				int tmp=input[i];
				input[i]=input[j];
				input[j]=tmp;
			}
		}
	}
}

/*
 * 快速排序
 * 先随机选中一个数，把数组中比这个数大的所有
 * 数放在一边，比它小的放在另一边，完成一次排
 * 序，然后分别对两部分的数再进行上面的流程，
 * 一直分割排序直到最后分成一个数没办法再分。
 *
 * 需要注意的地方，
 * 1，分割点返回值不再参与比较
 * 2.如果起始值就是最小值
 * 3.如何移动比mid小的值到mid前面，（保持low不
 * 动， 然后，依次把比mid小的值按顺序填充，完
 * 成之后再把mid移动到相应位置。
 * */
void quick_sort(int *input,int len)
{
	/*
	 * 该partition函数主要是将比mid大的数放到右边，比mid
	 * 小的放到左边，同时返回mid的位置。排序时候以起始值
	 * low不动为，移动完之后，再放置mid值的位置到它应该的
	 * 的位置。
	 * */
	int partition(int * input,int low,int high)
	{
		int i=low;
		int j=low+1;
		int mid=input[low];
		/*每次比较都不比较mid*/
		while(i<high&&j<high)
		{
			/*
			 * 把比mid小的数依出现顺序依次放到mid前的位置上
			 * j是已经填了几个比mid小的数，j=0的位置是留给
			 * 了mid值本身。
			 * */
			if(input[i]<mid)
			{
				int tp=input[j];
				input[j]=input[i];
				input[i]=tp;
				j++;
			}
			i++;
		}
		/*
		 * 最后交换处于开头的mid值和最后一个
		 * 比mid小的值的位置，这样来恰好使
		 * mid位于分割位置上。
		 * */
		input[low]=input[j-1];
		input[j-1]=mid;
		/*返回mid的位置，每次比较都不含mid*/
		return j-1;
	}
	void sort(int *input,int low,int high)
	{
		if(low<high)
		{
			int flag=partition(input,low,high);
			/*
			 * 如果恰好起始值input[low]就是最小值，
			 * 那么就把整体比较的部分向右偏移一位。
			 * */
			if(flag==low)
			{
				flag+=1;
				low+=1;
			}
			if(low<high)
			{
				//                printf("flag :%dlow:%d,high:%d\n",input[flag],low,high);
				sort(input,low,flag);
				sort(input,flag,high);
			}
		}
	}
	sort(input,0,len);
}

/*
 *
 * 归并排序法
 * 首先是将数组分割成小块，然后合并过程排序。
 * 需要注意地方：
 * 1.终止条件，如果没设置好会出现low0，mid0，high1
 * 递归无法返回
 * 2.合并过程中，一定要清楚的是两个数组各自增加比较
 * 3.每次用临时数组的合并之后要记得更新原始的数组
 * 4.因为在合并比较的时候采取的合并策略是，保留low，
 * 把mid位数据划分在第二个数组，同时第二个数组中没有
 * high，所有要在初始条件时用len作为high的起始，这样
 * 排序时就不会没有把最后一个元素排好。
 * */
void merge_sort(int *input,int len)
{
	void  merge_array(int low,int high,int mid,int *src,int *dst)
	{
		int i=low;
		int j=mid;
		int k=low;
		while(i<mid&&j<high)
		{
			if(src[i]<src[j])
			{
				dst[k]=src[i];
				i++;
			}
			else
			{
				dst[k]=src[j];
				j++;
			}
			k++;
		}
		while(i<mid)
		{
			dst[k++]=src[i++];
		}
		while(j<high)
		{
			dst[k++]=src[j++];
		}
		for(i=low;i<high;i++)
		{
			src[i]=dst[i];
		}
	}
	void merge_sort(int low,int high,int * src,int *dst)
	{
		int mid=(low+high)/2;
		if(low<high&&low!=mid)
		{
			merge_sort(low,mid,src,dst);
			merge_sort(mid,high,src,dst);   
			merge_array(low,high,mid,src,dst);     
		}
	}
	int *dst=(int *)malloc(sizeof(int)*len);
	memset(dst,0,len);
	merge_sort(0,len,input,dst);
	free(dst);
}

/*
 * 问题1，为什么最后一个非终端节点是第[n/2]个元素。
 * 分析，因为树的结构是一个完全二叉树，所以所有的
 * 元素基本被均分成两半。可以用归纳法来推理下，…
 *
 * 问题2，为什么要找最后一个非终端节点呢？找到最后
 * 一个非终节点之后就能逆向遍历所有的非终节点。从而
 * 根据堆的定义调整数据结构。k(i)<=k(2i) && k(i)<=
 * k(2i+1);
 *
 * 这个才是正确的heap_sort，heap_sort是基于这样的前
 * 提的，除了当前元素外的其他元素都已经是按照堆排序
 * 的。而上一个所谓的堆排序算法，实际上近似于bub_so
 * rt.
 * */
void heap_sort(int *input,int len)
{
	void heap_adjust(int *input,int pos, int len)
	{
		int j;
		int pn=pos;
		int tp=input[pos-1];
		/*
		 * j为非终端节点位置从1开始
		 * */
		for(j=pos*2;j<=len;j*=2)
		{
			if(j+1<=len)
			{
				if(tp>=input[j-1] && tp>=input[j])
				{
					break;
				}
				if(input[j-1]>input[j])
				{//check the pos*2 none-leaf-node
					input[pn-1]=input[j-1];
					input[j-1]=tp;
				}
				else
				{
					input[pn-1]=input[j];
					input[j]=tp;
					j=j+1;
				}
			}
			else
			{
				if(tp>=input[j-1])
				{
					break;
				}
				else
				{
					input[pn-1]=input[j-1];
					input[j-1]=tp;
				}
			}
			pn=j;
		}
	}
	void build_heap(int *input,int len)
	{
		int i;
		for(i=len/2;i>0;i--)
		{
			heap_adjust(input,i,len);
		}
	}
	void sort_heap(int *input,int len)
	{
		int i=len;
		int tp;
		while(i>1)
		{
			tp=input[i-1];
			input[i-1]=input[0];
			input[0]=tp;
			i=i-1;
			heap_adjust(input,1,i);
		}
	}
	build_heap(input,len);
	sort_heap(input,len);
}

/*
 * 相同元素计数
 * 计算方法是，先将当前元素存入临时变量tmp
 * 然后比较每个元素是否和tmp相等，同时对相
 * 同元素用k计数，如果当前元素和tmp不等，那
 * 么就将当前元素赋值给tmp，同时计数器数组
 * 移动到下一个存储位置，并将当前元素次数从
 * 1开始计。
 * 程序小技巧点，每次都更新下freq中的值，这
 * 样就能保证最后的结果是正确的。
 * */
int * freq_count(int *input,int len)
{
	int i=0;
	int *freq=(int *)malloc(sizeof(int)*len);
	for(i=0;i<len;i++)
	{
		freq[i]=input[i];
	}
	int j=0;
	int k=0;
	int tmp=input[0];
	for(i=0;i<len;i++)
	{
		if(input[i]==tmp)
		{
			k++;
		}
		else
		{
			tmp=input[i];
			k=1;
			j+=1;
		}
		freq[j]=k;
	}
	if(j!=len-1)
	{
		freq[j+1]=0;
	}
	return freq;
}

void set_sort_fun( char * sort_name,void (**sort_func)(int *,int) )
{
	if(strcmp(sort_name,"Bubble")==0)
	{
		*sort_func=bub_sort;
	}
	if(strcmp(sort_name,"qsort")==0)
	{
		*sort_func=quick_sort;
	}
	if(strcmp(sort_name,"merge")==0)
	{
		*sort_func=merge_sort;
	}
	if(strcmp(sort_name,"heap")==0)
	{
		*sort_func=heap_sort;
	}
}
int main(int argc,char *argv[])
{

	srand( (double)time(NULL));
	int len=8;
	/*输入数组长度*/
	//    scanf("%d",&len);
	void (*sort)(int *input,int len);
	int * input=(int *)malloc(sizeof(int)*len);
	int i=0;
	/*输入数组元素*/
	puts("待排序数组：");
	for(i=0;i<len;i++)
	{
		//        scanf("%d",input+i);
		input[i]=rand()%100;
		printf("%d\t",*(input+i));
	}
	printf("\n");
	/*排序*/
	set_sort_fun("heap",&sort);
	sort(input,len);
	puts("排序后数组：");
	prinpt(input,len);
	/*相同元素计数*/
	int *freq=freq_count(input,len);
	for(i=0;i<len;i++)
	{
		if(freq[i])
		{
			printf("freq:%d\n",freq[i]);
		}
		else
		{
			break;
		}
	}
	return 0;

}


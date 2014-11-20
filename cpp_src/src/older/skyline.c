/*
 * Author:haiy
 * Date:August 21 2013
 * Description:http://ds.fzu.edu.cn/Uploads/Problem/skyline.pdf
 * */

#include<stdio.h>
#include<stdlib.h>

typedef struct line
{
	int x_val;
	int y_val;
	struct line * pn;
}line,*line_ptr;

void build_skyline(line_ptr skyline,int *input)
{
	line_ptr cur=skyline;
	while(cur->pn)
	{
		if(cur->x_val < input[0] &&
				cur->pn->x_val > input[0])
		{
			line_ptr mid=(line_ptr)malloc(sizeof(line));
			mid->x_val=input[0];
			mid->y_val=(cur->y_val>input[1]?cur->y_val:input[1]);
			mid->pn=cur->pn;
			cur->pn=mid;
		}
		else if(cur->x_val < input[2] &&
				cur->pn->x_val > input[2])
		{
			line_ptr mid=(line_ptr)malloc(sizeof(line));
			mid->x_val=input[2];
			mid->y_val=cur->y_val;
			mid->pn=cur->pn;
			cur->pn=mid;
		}
		else if(input[0] <= cur->x_val &&
				input[1] >= cur->x_val)
		{
			cur->y_val=cur->y_val>input[1]?cur->y_val:input[1];
		}
		cur=cur->pn;
	}
	if(cur->pn==NULL &&( input[0] < cur->x_val && cur->x_val < input[2] ))
	{
		line_ptr last=(line_ptr)malloc(sizeof(line));
		last->pn=NULL;
		last->x_val=input[2];
		last->y_val=0;
		cur->y_val=input[1];
		cur->pn=last;
	}
	if(cur->pn==NULL &&(  cur->x_val < input[0] ))
	{
		line_ptr last=(line_ptr)malloc(sizeof(line));
		last->x_val=input[0];
		last->y_val=input[1];
		cur->pn=last;
		last=(line_ptr)malloc(sizeof(line));
		last->y_val=0;
		last->x_val=input[2];
		cur->pn->pn=last;
		last->pn=NULL;
	}
	cur=skyline;
	while(cur->pn)
	{
		if(cur->y_val==cur->pn->y_val)
		{
			line_ptr tp=cur->pn;
			cur->pn=cur->pn->pn;
			free(tp);
		}
		cur=cur->pn;
	}
}

void main()
{
	int n;
	scanf("%d",&n);

	int *input=(int *)malloc(sizeof(int)*3);
	line_ptr skyline=(line_ptr)malloc(sizeof(line));
	scanf("%d%d%d",input+0,input+1,input+2);
	skyline->x_val=input[0];
	skyline->y_val=input[1];
	skyline->pn=(line_ptr)malloc(sizeof(line));
	skyline->pn->x_val=input[2];
	skyline->pn->y_val=0;
	skyline->pn->pn=NULL;
	
	int i=0;
	line_ptr last_pre=skyline;
//	printf("%d,%d,%d\n",input[0],input[1],input[2]);
	for(i=0;i<n;i++)
	{
		scanf("%d%d%d",input+0,input+1,input+2);
//		printf("%d,%d,%d\n",input[0],input[1],input[2]);
//		last_pre=merge_skyline(last_pre,input);
		build_skyline(skyline,input);
	}
	line_ptr cur=skyline;
	while(cur)
	{
		printf("%d %d ",cur->x_val,cur->y_val);
		cur=cur->pn;
	}
	printf("\n");
}

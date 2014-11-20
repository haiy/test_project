/*
 * Author:haiy
 * Date:Aug 26 2013
 * Description:http://ds.fzu.edu.cn/Uploads/Problem/dom.pdf
 * */

#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n;
    scanf("%d",&n);
    int i;
    int *D=(int *)malloc(sizeof(int)*n);
    for(i=0;i<n;i++)
    {
        scanf("%d",D+i);
    }
    /*
     * 循环遍历，找到亲兄弟
     * */
    for(i=0;i<n-1;i++)
    {
    //    printf("cur D[%d]:%d\n",i,D[i]);
        int j;
        int o=D[i];
        for(j=i+1;j<n;j++)
        {
            if(D[j]>=D[i])
            {
                D[i]=j;
                break;
            }
            else
            {
                if(j==n-1&&D[i]==o)
                {
                    D[i]=-1;
                    break;
                }
            }
        }
        printf("%d ",D[i]);
    }
    D[n-1]=-1;
    printf("%d",D[i]);
    printf("\n");
    free(D);
    return 0;
}

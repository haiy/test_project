/*
 * Author:haiy
 * Date:August 22
 * Description：ds.fzu.edu.cn+ballgame.pdf
 * DO WHAT YOU WANT!
 * */
#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n;
    scanf("%d",&n);
    int *b1=(int *)malloc(sizeof(int)*n);
    int *b2=(int *)malloc(sizeof(int)*n);
    int j;
    /*输入两组小球*/
    for(j=0;j<n;j++)
    {
        scanf("%d",b1+j);
    }
    for(j=0;j<n;j++)
    {
        scanf("%d",b2+j);
    }
    /*tranverse the array to check if it's able
     * to accept the chanllenge
     * */
    int i;
    for(j=0,i=0;i<n,j<n;j++,i++)
    {
        //printf("1 Now is b1[%d]:%d\tb2[%d]:%d\n",i,b1[i],j,b2[j]);
        if(b1[i]!=b2[j])
        {
            int flag=j;
            /* 
             * find the original position of b[i]
             * in b[2]
             * */
            while(flag<n)
            {
                //printf("2 Now is b1[%d]:%d\tb2[%d]:%d\n",i,b1[i],flag,b2[flag]);
                if(b1[i]==b2[flag])
                {
                    break;
                }
                flag=flag+1;
            }

            //printf("3 Now is b1[%d]:%d\tb2[%d]:%d\n",i,b1[i],flag,b2[flag]);
            while(i<n&&flag>=0)
            {
                if(b1[i]==b2[flag])
                {
                    i=i+1;
                    flag=flag-1;
                }
                else
                {
                    flag=-1;
                    puts("Reject!");
                    break;
                }
            }
            if(flag==-1)
            {
                break;
            }
            //printf("5 Now is b1[%d]:%d\tb2[%d]:%d\n",i,b1[i],flag,b2[flag]);
            j=i;
        }
    }

    if(i==n)
    {
        puts("Accept!");
        for(j=0,i=0;i<n,j<n;i++,j++)
        {
            //printf("in out i:%d\n",i);
            if(b1[i]!=b2[j])
            {
                int flag=j;
                while(flag<n)
                {
                    if(b1[i]==b2[flag])
                    {
                        break;
                    }
                    puts("in");
                    flag+=1;
                }
                puts("in");
                while(i<flag)
                {
                    puts("out");
                    i+=1;
                }
                puts("out");
                printf("Now i:%d j:%d\n",i,j);
                j=i;
            }
            else
            {
                puts("in\nout");
            }
        }
    }
    return 0;
}

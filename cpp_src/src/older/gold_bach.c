/*
 * ���ߣ�haiy
 * ���䣺haiyangfu512@gmail.com
 * ˵��������Ҫ����Դ��http://ds.fzu.edu.cn/Uploads/Problem/goldbach.pdf
 *      ��Ҫ����֤��°ͺղ��롣
 * ���ڣ�7��25
 *
 * ����1����ֱ�Ӷ�ÿ�����Ƿ������������ж�
 * ����2�������з��������������
 * ����2���ȽϺá�
 * Ϊʲô�أ������ǹ����ԱȽ�С���֣����������ǹ����ԱȽϴ�Ĳ��֣�
 * ���Խ������Դ�Ķ��޳�֮������Ȼʣ�µĶ��������
 * */

#include<stdlib.h>
#include<string.h>
#include<stdio.h>


/*���N�Ƿ�������*/
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
/* ����1���ҳ�����С��R������, ֱ�ӳ�
 * */
char * lower_prime(int R)
{
    /*��һ��0��1�ַ�������ʾ��Ӧλ�õ���ֵ�ǲ���
     * ����
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

/*����2��ɸѡ��*/
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


/*����õ��������������м�������
 * ��ӵĺ͵�������ķ�Χ��R����
 * ����Ҫ����˳����Ӽ���ķ�����
 * Ҳ����˵����ʵÿ������������
 * �����е��±������ֵ��Ȼ������
 * �д�ŵ��Ǳ�־1����0��ֻҪ����
 * һ������λ�þ����ж����ܲ���
 * �����������ĺ͵���R��
 * ����˵R=11����res[5]='1',��ô5
 * ��С��11����������Ҫ5+x=11����
 * ôx=6����ʱ��res[6]=0������
 * ����������5�����㡣Ҳ����˵û��
 * ��С��11��������5�ĺ͵���11. 
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

/*����2��*/
int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        printf("Parameter Error! Find  %d arguments\n",argc);
        exit(0);
    }
    printf("arg1:%s\targ2:%s\n",argv[0],argv[1]);
    int R=atoi(argv[1]);
    /*�ı�lower_prime���ò�ͬ�ļ������*/
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

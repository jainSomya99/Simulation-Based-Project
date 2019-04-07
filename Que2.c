
#include<stdio.h>
int main()
{	int process[3]={2132,2102,2453};
	int burst[3]={2,4,8};
	int at[3]={0,0,0};
	int c1=0,c2=0,c3=0;
	printf(" Longest remaining time first: \n");
	for(int i=3;i>2;i--)
	{	for(int j=burst[i];j>0;j--)
		{
			if(burst[i]>burst[i-1] && burst[i]>burst[i-2])
			{
				burst[i]--;
				c1=c1+1;
			}
			else if(burst[i]==burst[i-1])
			{
				if(process[i]<process[i-1])
				{
					burst[i-1]--;
					c2=c2+1;
				}
				else
				{
					burst[i]--;
					c1=c1+1;
				}
			}
			else if(burst[i]==burst[i-2])
			{
				if(process[i]<process[i-2])
				{
					burst[i-2]--;
					c3=c3+1;
				}
				else
				{
					burst[i]--;
					c1=c1+1;
				}
			}
		}
	}
	printf("completion time for process 1:%d \n",c1);
	printf("completion time for process 2:%d\n",c2);
	printf("completion time for process 3:%d\n",c3);
}

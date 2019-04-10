
#include<stdio.h>
//A structure for storing all details of processes.
struct process
{
    int AT,BT,WT,BTbackup,CT,TAT,runcount;
}p[10];//an array of objects of struct process
int totaltime = 0;
int prefinaltotal = 0;
int n;
void input()
{
    int i;
	printf("\nEnter number of processes");
	scanf("%d",&n);
	printf("\nEnter arrival time of processes:");
	for(i=0;i<n;i++)
	{
		printf("\nFor process %d:",i+1);
		scanf("%d",&p[i].AT);
	}
	printf("\nEnter burst time for processes:");
	for(i=0;i<n;i++)
	{
		printf("\nFor process %d:",i+1);
		scanf("%d",&p[i].BT);
		p[i].BTbackup=p[i].BTbackup;
		prefinaltotal += p[i].BT;
	}
}
int compare(int i,int j)
{
    // compare the id of two processes to break tie
    return p[i].AT< p[j].AT;
}
int findsmallest()
{
    int min = n, i;
    p[min].BT=9999999;
    for (i = 0; i <n; i++)
    {
        if(p[i].runcount==1)
        {
            continue;
        }
        if (p[i].BT < p[min].BT)
            min = i;
        else if(p[min].BT==p[i].BT)
        {
            if(compare(i,min))
            min=i;
        }
        else
            continue;
    }
    // returning the index of the process having the largest BT
    return min;
}
void SJF()
{
    int index;
    int flag = 0;
    for(index=0;index<n;index++)
    {
        p[index].runcount=0;
    }
    while (1)
    {
        index = findsmallest();
        p[index].runcount=1;
        printf("Process executing at time %d is: P%d\n",totaltime,index + 1);
        totaltime += p[index].BT;
        p[index].BT =0;
        p[index].CT = totaltime;
        printf(" Process P%d is completed at %d\n",index+1,totaltime);
        // loop termination condition
        if (totaltime == prefinaltotal)
            break;
    }
}
void RR(int tq)
{
    int count,remain=n,flag=0;
    for(count=0;count<n;count++)
    {
        p[count].runcount=0;
    }

  //printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n");
  for(count=0;remain!=0;)
  {
    if(p[count].BT<=tq && p[count].BT>0)
    {
         printf("Process executing at time %d is: P%d\n",totaltime,count + 1);
      totaltime+=p[count].BT;
      p[count].BT=0;
      p[count].CT=totaltime;
      printf(" Process P%d is completed at %d\n",count+1,totaltime);
    }
    else if(p[count].BT>0)
    {
        printf("Process executing at time %d is: P%d\n",totaltime,count + 1);
      p[count].BT-=tq;
      totaltime+=tq;
      p[count].runcount++;
    }
    if(p[count].runcount==1)
    {
        remain--;
    }
    if(count==n-1)
      count=0;
    else if(p[count+1].AT<=totaltime)
      count++;
    else
      count=0;
  }
}
int main()
{
	int i;
	double avgT=0;
	double avgW=0;
	int minAT=0;
	input();
	//calculate minimum AT for initial time when execution starts
	for(i=1;i<n;i++)
        if(p[minAT].AT>p[i].AT)
            minAT=i;
	// calculating initial time when execution starts
    totaltime += p[minAT].AT;
    // calculating to terminate loop
    prefinaltotal += p[minAT].AT;

	printf("First Iteration(TQ=3)\n");
	RR(3);
	/*while(1)
	{
		if(p[i].AT<=tq1+p[i-1].AT)
		{
			p[i].BT=p[i].BT-tq1;
			printf("\nprocess %d",i+1);
			printf("\nLeft=%d",p[i].BT);
		}
		else
		{
			p[i].BT=p[i].BT-tq1;
			printf("\nprocess %d ",i+1);
			printf("\nLeft= %d",p[i].BT);
		}
	}*/

	printf("\nSecond Iteration(TQ=6)\n");
	RR(6);
	/*for(i=0;i<n;i++)
	{
		if(p[i].AT<=tq2+p[i-1].AT)
		{
			p[i].BT=p[i].BT-tq2;
			printf("\nprocess %d",i+1);
			printf("\nLeft= %d",p[i].BT);
		}
		else
		{
			p[i].BT=p[i].BT-tq2;
			printf("\nprocess %d",i+1);
			printf("\nLeft= %d",p[i].BT);
		}
	}
	*/
	printf("\nThird Iteration(SJF)\n");
	SJF();
	for(i=0;i<n;i++)
	{
		p[i].TAT=p[i].CT-p[i].AT;
		p[i].WT=p[i].TAT-p[i].BTbackup;
		printf("\nCompletion time for process%d:%d \n",i+1,p[i].CT);
		printf("Turn around time for process:%d:%d \n",i+1,p[i].TAT);
		printf("Waiting time for process:%d : %d \n",i+1,p[i].WT);
		avgT=avgT+p[i].TAT;
		avgW=avgW+p[i].WT;
	}
	avgT=avgT/n;
	avgW=avgW/n;
	printf("\nAverage turn around time: %f",avgT);
	printf("\nAverage waiting time:%f",avgW);
}

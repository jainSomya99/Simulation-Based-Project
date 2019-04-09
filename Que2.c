//#include <bits/stdc++.h>
#include<stdio.h>
// creating a structure of a process
struct process {
    int id;
    int BT;
    int BTbackup;   // for backup purpose to print in last
    int WT;
    int TAT;
    int CT;
};
// creating object's array for 3 processes.
struct process p[3];

// variable to find the total time
int totaltime = 0;
int prefinaltotal = 0;

// comparator function for sort()
int compare(struct process p1,struct process p2)
{
    // compare the id of two processes to break tie
    return p1.id< p2.id;
}

// computing the largest burst Time among all the available processes
int findlargest()
{
    int max = 0, i;
    for (i = 0; i < 3; i++)
    {
        if (p[i].BT > p[max].BT)
            max = i;
        else if(p[max].BT==p[i].BT)
        {
            if(p[max].id>p[i].id)
                max=i;
        }
        else
            continue;
    }
    // returning the index of the process having the largest BT
    return max;
}

// function to find the completion time of each process
int findCT()
{
    int index;
    int flag = 0;
    while (1)
    {
        index = findlargest();
        printf("Process executing at time %d is: P%d\n",totaltime,index + 1);
        p[index].BT -= 1;
        totaltime += 1;
        if (p[index].BT == 0)
        {
            p[index].CT = totaltime;
            printf(" Process P%d is completed at %d\n",p[index].id,totaltime);
        }
        // loop termination condition
        if (totaltime == prefinaltotal)
            break;
    }
}

int main()
{

    int i;

    // initializing the process number
    p[0].id=2132;
    p[1].id=2102;
    p[2].id=2453;

    // cout<<" Burst time of 4 processes : ";
    p[0].BT=2;
    p[1].BT=4;
    p[2].BT=8;
    for (i = 0; i < 3; i++)
    {
        // backup for displaying the output in last
        // calculating total required time for terminating the function
        p[i].BTbackup = p[i].BT;
        prefinaltotal += p[i].BT;
    }

    // displaying the process before executing
    printf("PNo\tID\tBT\n");

    for (i = 0; i < 3; i++) {
           printf("%d\t%d\t%d\n",i+1, p[i].id, p[i].BT);
    }
    printf("\n");
    // calculating initial time when execution starts
    totaltime += 0;

    // calculating to terminate loop
    prefinaltotal += 0;
    findCT();
    int totalWT = 0;
    int totalTAT = 0;
    for (i = 0; i < 3; i++) {
        // since, TAT = CT - AT
        p[i].TAT = p[i].CT;
        p[i].WT = p[i].TAT - p[i].BTbackup;

        // finding total waiting time
        totalWT += p[i].WT;

        // finding total turn around time
        totalTAT += p[i].TAT;
    }

    printf("After execution of all processes ... \n");

    // after all process executes
    printf("PNo\tID\tBT\tCT\tTAT\tWT\n");

    for (i = 0; i < 3; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",i+1,p[i].id,p[i].BTbackup,p[i].CT,p[i].TAT,p[i].WT);
    }
    printf("\nTotal TAT = %d\n",totalTAT);
    printf("Average TAT = %f\n",totalTAT/4.0);
    printf("Total WT = %d\n",totalWT);
    printf("Average WT = %f\n",totalWT / 4.0);
    return 0;
}

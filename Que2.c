
//#include <bits/stdc++.h>
#include<stdio.h>

// creating a structure of a process
struct process {
    int processno;
    int AT;
    int BT;
    // for backup purpose to print in last
    int BTbackup;
    float WT;
    float TAT;
    int CT;
};

// creating a structe of 4 processes
struct process p[3];

// variable to find the total time
int totaltime = 0;
int prefinaltotal = 0;

// comparator function for sort()
int compare(struct process p1,struct process p2)
{
    // compare the Arrival time of two processes
    return p1.AT < p2.AT;
}

// finding the largest Arrival Time among all the available
// process at that time
int findlargest(int at)
{
    int max = 0, i;
    for (i = 0; i < 4; i++) {
        if (p[i].AT <= at) {
            if (p[i].BT > p[max].BT)
                max = i;
        }
    }

    // returning the index of the process having the largest BT
    return max;
}

// function to find the completion time of each process
int findCT()
{
    int index;
    int flag = 0;
    int i = p[0].AT;
    while (1) {
        if (i <= 4) {
            index = findlargest(i);
        }

        else
            index = findlargest(4);
        printf("Process executing at time %d is: P%d\n",totaltime,index + 1);

        p[index].BT -= 1;
        totaltime += 1;
        i++;

        if (p[index].BT == 0) {
            p[index].CT = totaltime;
            printf(" Process P%d is completed at %d\n",p[index].processno,totaltime);
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
    p[0].processno=2132;
    p[1].processno=2102;
    p[2].processno=2453;

    // cout<<"arrival time of 4 processes : ";
    for (i = 0; i < 3; i++) // taking AT
    {
        p[i].AT = 0;
    }

    // cout<<" Burst time of 4 processes : ";
    p[0].BT=2;
    p[1].BT=4;
    p[2].BT=8;
    for (i = 0; i < 3; i++) {

        // assigning {2, 4, 6, 8} as Burst Time to the processes
        // backup for displaying the output in last
        // calculating total required time for terminating
        // the function().
        p[i].BTbackup = p[i].BT;
        prefinaltotal += p[i].BT;
    }

    // displaying the process before executing
    printf("PNo\tAT\tBT\n");

    for (i = 0; i < 3; i++) {
           printf("\t%d\t%d\t%d\n",p[i].processno, p[i].AT, p[i].BT);
    }
    printf("\n");

    // soritng process according to Arrival Time
    //sort(p, p + 3, compare);

    // calculating initial time when execution starts
    totaltime += p[0].AT;

    // calculating to terminate loop
    prefinaltotal += p[0].AT;
    findCT();
    int totalWT = 0;
    int totalTAT = 0;
    for (i = 0; i < 3; i++) {
        // since, TAT = CT - AT
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BTbackup;

        // finding total waiting time
        totalWT += p[i].WT;

        // finding total turn around time
        totalTAT += p[i].TAT;
    }

    printf("After execution of all processes ... \n");

    // after all process executes
    printf("PNo\tAT\tBT\tCT\tTAT\tWT\n");

    for (i = 0; i < 3; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].processno,p[i].AT,p[i].BTbackup,p[i].CT,p[i].TAT,p[i].WT);
    }
    printf("\nTotal TAT = %d\n",totalTAT);
    printf("Average TAT = %d\n",totalTAT);
    printf("Total WT = %d\n",totalWT);
    printf("Average WT = %d\n",totalWT / 4.0);
    return 0;
}

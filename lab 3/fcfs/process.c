#include<stdio.h>

struct process{
    int pid;
    int burstTime;

};
typedef struct process process ;

int main(){
    int n;
    printf("\nEnter no of process : ");
    scanf("%d",&n);
    process p[n];

    for (int i = 0; i < n; i++)
    {
        p[i].pid=i+1;
        printf("\nEnter burst time : ");
        scanf("%d",&p[i].burstTime);
    }
    int wait[n],turn[n];
    wait[0]=0;
    turn[0]=p[0].burstTime;
    for (int i = 1; i < n; i++)
    {
        wait[i]=wait[i-1] + p[i-1].burstTime;
        turn[i]=wait[i]+p[i].burstTime;
    }
    
        printf("PID  burstTime WaitTime TurnAroundTime \n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\n",p[i].pid,p[i].burstTime,wait[i],turn[i]);
    }
    

    return 0;
    

}


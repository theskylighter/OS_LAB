#include<stdio.h>

typedef struct process{
    int pid;
    int burstTime;
    int priority;
}
process;

void swapProcess(process* arr ,int index1,int index2 ){
    process temp=arr[index1];
    arr[index1]=arr[index2];
    arr[index2]=temp;

}
int main(){
    int n;
    printf("\nEnter no of process : ");
    scanf("%d",&n);
    process p[n];
//INPUT
     for (int i = 0; i < n; i++)
    {
        p[i].pid=i+1;
        printf("\nfor P %d\nEnter burst time : ",i+1);
        scanf("%d",&p[i].burstTime);
        printf("\nEnter priority : ");
        scanf("%d",&p[i].priority);
    
    }

//bubble SORt Process based on priority
    for(int i=0;i<n-1;i++){
        for (int j = 0; j < n-1-i; j++)
        {
            if (p[j].priority<p[j+1].priority){
                swapProcess(p,j,j+1);
            }
        }
        
    }
    int wait[n],turn[n];

    wait[0]=0;
    turn[0]=p[0].burstTime;
    for (int i = 1; i < n; i++)
    {
        wait[i]=wait[i-1] + p[i-1].burstTime;
        turn[i]=wait[i]+p[i].burstTime;
    }
    
        printf("\nPID  burstTime WaitTime TurnAroundTime \n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\n",p[i].pid,p[i].burstTime,wait[i],turn[i]);
    }

  float avg_wait,avg_turnaround;
  float sum_wait=0,sum_ta=0;
  for(int i=0;i<n;i++){
    
    sum_wait+=wait[i];
    sum_ta+=turn[i];
  }
  avg_turnaround=sum_ta/n;
  avg_wait=sum_wait/n;
 
  printf("The avearge waiting time is: %f \n",avg_wait);
  printf("The avearge turn around time is: %f \n",avg_turnaround);

    return 0;
    

}


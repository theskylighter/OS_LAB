#include<stdio.h>

int main(int argc, char const *argv[])
{
	int n;
	printf("ENTER no. of process : ");
	scanf("%d",&n);
	
	int arr[n];
	printf("\nENTER arrival times : \n");
	for(int i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}

	int bur[n];
	printf("\nENTER burst times : \n");
	for(int i=0;i<n;i++){
		scanf("%d",&bur[i]);
	}

	// int waiting_time[n];
	
	// waiting_TIME & turnAround_TIME
	// for p0,
	int time=0;
	int waitTime=0;
	int turnATime=0;

	turnATime=bur[0];
	
	for(int i=0;i<n;i++){
		// If the current time is less than the arrival time, CPU remains idle
        if (time < arr[i]) {
            time = arr[i];
        }
		waitTime= time -arr[i];
		time+=bur[i];
		turnATime= waitTime+bur[i];
		
		printf("\nFor p%d :",i);
		printf("WT = %d, TAT = %d :",waitTime,turnATime);

	}

	return 0;
}
#include <stdio.h>
#include <limits.h>

typedef struct Process {
    int pid;
    int bursttime;
    int arrivaltime;
    int priority;
    int remainingtime;
} process;

int main() {
    int n;
    printf("Enter the number of processes: \n");
    scanf("%d", &n);
    
    process p[n];
    int wait[n], turnaround[n], completed = 0, current_time = 0;
    float total_wait_time = 0, total_turnaround_time = 0;

    // Taking input for each process
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter the burst time for process %d: ", p[i].pid);
        scanf("%d", &p[i].bursttime);
        printf("Enter the arrival time for process %d: ", p[i].pid);
        scanf("%d", &p[i].arrivaltime);
        printf("Enter the priority for process %d: ", p[i].pid);
        scanf("%d", &p[i].priority);
        p[i].remainingtime = p[i].bursttime; // Initialize remaining time
    }

    while (completed < n) {
        int highest_priority_index = -1;
        int highest_priority = INT_MAX;

        // Find the process with the highest priority that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            if (p[i].arrivaltime <= current_time && p[i].remainingtime > 0 && p[i].priority < highest_priority) {
                highest_priority = p[i].priority;
                highest_priority_index = i;
            }
        }

        if (highest_priority_index == -1) {
            // No process is ready to run, so we increment the current time
            current_time++;
            continue;
        }

        // Execute the process with the highest priority for one time unit
        p[highest_priority_index].remainingtime--;
        current_time++;

        // If the process is completed
        if (p[highest_priority_index].remainingtime == 0) {
            completed++;
            turnaround[highest_priority_index] = current_time - p[highest_priority_index].arrivaltime;
            wait[highest_priority_index] = turnaround[highest_priority_index] - p[highest_priority_index].bursttime;

            total_wait_time += wait[highest_priority_index];
            total_turnaround_time += turnaround[highest_priority_index];
        }
    }

    // Print the results
    printf("PID   ArrivalTime  BurstTime  Priority  WaitingTime  TurnaroundTime\n");
    for (int i = 0; i < n; i++) {
        printf("%d     %d            %d          %d         %d            %d\n", 
               p[i].pid, p[i].arrivaltime, p[i].bursttime, p[i].priority, wait[i], turnaround[i]);
    }

    // Print the average waiting and turnaround times
    printf("The average waiting time is: %f \n", total_wait_time / n);
    printf("The average turnaround time is: %f \n", total_turnaround_time / n);

    return 0;
}
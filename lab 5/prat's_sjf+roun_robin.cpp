//program 1: pre-emptive SJF

#include <stdio.h>
#include <limits.h>

struct process {
    int pid;
    int arival;
    int bust;
    int remtime;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

void SJF(struct process p[], int n) {
    int completed = 0, timer = 0, min_time;
    int shortest = 0;
    int finish_time;
    int is_done = 0;

    // Loop until all processes are completed
    while (completed != n) {
        min_time = INT_MAX;

        // Select the process with the minimum remaining time
        for (int i = 0; i < n; i++) {
            if (p[i].arival <= timer && p[i].remtime > 0 && p[i].remtime < min_time) {
                min_time = p[i].remtime;
                shortest = i;
                is_done = 1;
            }
        }

        // If no process is available to execute, increment the timer
        if (is_done == 0) {
            timer++;
            continue;
        }

        // Decrease the remaining time of the selected process
        p[shortest].remtime--;

        // If a process gets completely executed
        if (p[shortest].remtime == 0) {
            completed++;
            is_done = 0;
            finish_time = timer + 1;

            // Calculate completion time, turnaround time and waiting time
            p[shortest].completion_time = finish_time;
            p[shortest].turnaround_time = finish_time - p[shortest].arival;
            p[shortest].waiting_time = p[shortest].turnaround_time - p[shortest].bust;
        }

        // Increment the timer
        timer++;
    }

    // Output results
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               p[i].pid, p[i].arival, p[i].bust, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &p[i].arival);

        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &p[i].bust);

        p[i].remtime = p[i].bust;
    }

    SJF(p, n);

    return 0;
}

//Program 2: Pre-emptive round robin

#include <stdio.h>

// Structure to store process information
typedef struct {
    int id;
    int at; // Arrival Time
    int bt; // Burst Time
    int rt; // Remaining Time
} Process;

// Function to sort processes by arrival time
void sortByArrival(Process processes[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].at > processes[j].at) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

int main() {
    int n, t, remain, flag = 0, tq;
    int wt = 0, tat = 0;

    printf("Enter Total Process:\t ");
    scanf("%d", &n);

    Process processes[n];
    
    remain = n;

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for Process Number %d :", i + 1);
        scanf("%d %d", &processes[i].at, &processes[i].bt);
        processes[i].rt = processes[i].bt;
    }

    printf("Enter Time Quantum:\t");
    scanf("%d", &tq);

    // Sort processes by arrival time
    sortByArrival(processes, n);

    printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n");
    int cnt;
    printf("Time quanta for this program is : %d ms\n", tq);
    printf("Intermediate Steps of Execution:\n");
    printf("Time\t|Process\t|Remaining Time\n");
    for (t = 0, cnt = 0; remain != 0;) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= t && processes[i].rt > 0) {
                printf("%d\t|P[%d]\t|%d\n", t, processes[i].id, processes[i].rt);
                if (processes[i].rt <= tq) {
                    t += processes[i].rt;
                    processes[i].rt = 0;
                    flag = 1;
                } else {
                    processes[i].rt -= tq;
                    t += tq;
                }

                if (processes[i].rt == 0 && flag == 1) {
                    remain--;
                    int turnaround_time = t - processes[i].at;
                    int waiting_time = turnaround_time - processes[i].bt;
                    printf("P[%d] completed at time %d\n", processes[i].id, t);
                    printf("P[%d]\t|\t%d\t|\t%d\n", processes[i].id, turnaround_time, waiting_time);
                    wt += waiting_time;
                    tat += turnaround_time;
                    flag = 0;
                }
                found = 1;
            }
        }

        // If no process is found, increment time
        if (!found) {
            t++;
            printf("%d\t|Idle\t|-\n", t);
        }
    }

    printf("\nProcess\t|Turnaround Time|Waiting Time\n\n");
    for (int i = 0; i < n; i++) {
        int turnaround_time = processes[i].bt + processes[i].at;
        for (int j = 0; j < n; j++) {
            if (processes[j].at < processes[i].at + processes[i].bt && processes[j].id != processes[i].id) {
                turnaround_time += processes[j].bt;
            }
        }
        int waiting_time = turnaround_time - processes[i].bt;
        printf("P[%d]\t|\t%d\t|\t%d\n", processes[i].id, turnaround_time, waiting_time);
    }

    printf("\nAverage Waiting Time= %f\n", wt * 1.0 / n);
    printf("Avg Turnaround Time = %f\n", tat * 1.0 / n);

    return 0;
}
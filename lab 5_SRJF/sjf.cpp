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
// Function to sort processes by burst time
void sortByBurst(Process processes[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].bt > processes[j].bt) {
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
    Process processes[10];

    printf("Enter Total Process:\t ");
    scanf("%d", &n);
    remain = n;

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for Process Number %d :", i + 1);
        scanf("%d %d", &processes[i].at, &processes[i].bt);
        processes[i].rt = processes[i].bt;
    }

    // printf("Enter Time Quantum:\t");
    // scanf("%d", &tq);

    // Sort processes by arrival time
    sortByArrival(processes, n);

    printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n");
    int cnt;
    for (t = 0, cnt = 0; remain != 0;) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= t && processes[i].rt > 0) {
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
                    printf("P[%d]\t|\t%d\t|\t%d\n", processes[i].id, t - processes[i].at, t - processes[i].at - processes[i].bt);
                    wt += t - processes[i].at - processes[i].bt;
                    tat += t - processes[i].at;
                    flag = 0;
                }
                found = 1;
            }
        }

        // If no process is found, increment time
        if (!found) {
            t++;
        }
    }

    printf("\nAverage Waiting Time= %f\n", wt * 1.0 / n);
    printf("Avg Turnaround Time = %f", tat * 1.0 / n);

    return 0;
}

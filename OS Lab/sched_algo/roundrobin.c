#include <stdio.h>
typedef struct {
    int pid;
    int at;
    int bt;
    int rt;
    int wt;
    int tat;
    int first_time;
    int response_time;
} Process;
void roundRobin(Process p[], int n, int quantum) {
    int time = 0, complete = 0;
    while(complete < n) {
        int idle = 1;
        for (int i = 0; i < n; i++) {
            if(p[i].rt>0 && p[i].at <= time) {
                idle = 0;
                if(p[i].rt == p[i].bt) {
                    p[i].first_time = time;
                    p[i].response_time = p[i].first_time - p[i].at;
                }
                if(p[i].rt > quantum ) {
                    time += quantum;
                    p[i].rt -= quantum;
                }
                else {
                    time += p[i].rt;
                    p[i].rt = 0;
                    p[i].tat = time - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    complete++;
                }
            }
        }
        if(idle==1) {
            time++;
            continue;
        }
    }
}
void printProcesses(Process p[], int n) {
    printf("\nPID  Arrival  Burst  Turnaround  Waiting  Response\n");
    for (int i = 0; i < n; i++) {
        printf("%3d  %7d  %5d  %10d  %7d  %8d\n", p[i].pid, p[i].at, p[i].bt, p[i].tat, p[i].wt, p[i].response_time);
    }
}
int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Process %d - Arrival Time: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Process %d - Burst Time: ", i + 1);
        scanf("%d", &p[i].bt);
        
        p[i].pid = i + 1;
        p[i].rt = p[i].bt;
        p[i].first_time = -1;
        p[i].response_time = -1;
    }
    printf("Enter time quantum: ");
    scanf("%d", &quantum);
    roundRobin(p, n, quantum);
    printProcesses(p, n);
    return 0;
}

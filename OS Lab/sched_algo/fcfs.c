#include<stdio.h>

void findWaitingTime(int processes[], int burst[], int n, int wt[]) {
    wt[0] = 0;
    for(int i = 1; i<n; i++) {
        wt[i] = burst[i-1] + wt[i-1];
    }
}
void findTurnAroundTime(int processes[], int burst[], int n, int wt[], int tat[]) {
    for(int i = 0; i<n; i++) {
        tat[i] = burst[i] + wt[i];
    }
}
void findResponseTime(int processes[], int n, int wt[], int rt[]) {
    for(int i = 0; i<n; i++) {
        rt[i] = wt[i];
    }
}
void print(int arr[], int n) {
    for(int i = 0; i<n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void averageTime(int processes[], int burst[], int n) {
    int wt[n], tat[n], rt[n];

    //tofindwaitingtme
    findWaitingTime(processes, burst, n, wt);
    //sum it up and divide by n

    //tofindturnaroundtime
    findTurnAroundTime(processes, burst, n, wt, tat);
    //sum it up and divide by n

    findResponseTime(processes, n, wt, rt);

    print(wt, n);
    print(tat, n);
}
int main() {
    //array of processes
    int processes[] = {1, 2, 3};
    int n = sizeof(processes)/sizeof(processes[0]);

    //array of burst times
    int burst[] = {5, 10, 15};

    //find average time of processes
    averageTime(processes, burst, n);
}
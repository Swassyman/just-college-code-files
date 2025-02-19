#include<stdio.h>
typedef struct process{
	int pid;
	int at;
	int bt;
	int rt;
	int wt;
	int tat;
}process;
void srtf(process p[],int n) {
	int time = 0;
	int complete = 0;
	while(complete<n) {
		int min_remaining = 999;
		int min_index = -1;
		for(int i = 0; i<n;i++) {
			if(p[i].at <= time && p[i].rt>0 && p[i].rt <= min_remaining) {
				min_remaining = p[i].rt;
				min_index = i;
			}
		}
		if(min_index==-1) {
			time++;
			continue;
		}
		p[min_index].rt--;
		time++;

		if(p[min_index].rt==0) {
			complete++;
			p[min_index].tat = time - p[min_index].at;
			p[min_index].wt = p[min_index].tat - p[min_index].bt;
		}
	}
}
void printProcesses(process p[], int n) {
    printf("PID  Arrival  Burst  Turnaround  Waiting\n");
    for (int i = 0; i < n; i++) {
        printf("%3d  %7d  %5d %10d  %7d\n", 
            p[i].pid, p[i].at, p[i].bt, p[i].tat, p[i].wt);
    }
}
int main() {
	printf("Enter the number of processes:");
	int n;
	scanf("%d",&n);
	process p[n];
	//inputting pid and burst time
	for(int i=0;i<n;i++) {
		printf("Enter the burst time of process %d:",i+1);	
		scanf("%d",&p[i].bt);
		printf("Enter the arrival time of process %d: ",i+1);
		scanf("%d",&p[i].at);
		p[i].pid=i+1;
		p[i].rt = p[i].bt;
	}
	srtf(p,n);
	printProcesses(p,n);
}
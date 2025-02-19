#include<stdio.h>
typedef struct process{
	int pid;
	int burst;
	int wt;
	int tat;
} process;
void sortProcesses(process p[],int n) {
	for(int i = 0; i < n-1; i++) {	
		for(int j = 0; j < n-i-1; j++) {
			if(p[j].burst > p[j+1].burst) {
				process temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
		}
	}
}
void findWaitingTime(process p[],int n) {
	for(int i = 1; i<n; i++) {
		p[i].wt = 0;
		for(int j = 0; j<i; j++){
			p[i].wt += p[j].burst;
		}
	}	
}
void findTurnAroundTime(process p[],int n) {
	for(int i = 0; i<n; i++) {
		p[i].tat = p[i].wt + p[i].burst;
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
		scanf("%d",&p[i].burst);
		p[i].pid=i+1;
	}
	//sorting according to burst time
	sortProcesses(p,n);
	//setting first process waiting time to be 0
	p[0].wt = 0;
	//find waiting time
	findWaitingTime(p,n);
	//calculate turn around time
	findTurnAroundTime(p,n);
	//print waiting time and turnaround time
	for(int i=0;i<n;i++) {
		printf("Process %d\t%d\t%d\n",p[i].pid,p[i].wt,p[i].tat);	
	}
}
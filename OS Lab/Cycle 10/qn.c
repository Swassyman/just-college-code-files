#include<stdio.h>
#include<stdbool.h>

bool isSafe(int P, int R, int alloc[][R], int max[][10], int avail[]) {

	int work[P];
	for(int i = 0; i<P; i++) {
		work[i] = avail[i];	
	}

	bool finish[P] = {false};
	int safeSeq[P];
	int count = 0;

	/*
		Iterating through process table until we find a process that can be allocated
		If 0 processes can be allocated at any iteration then system is not in safe state
	*/

	while(count < P) { //checking process list again and again
		bool found = false; //checking if any process can be allocated in any iteration
		for(int p = 0; p<P; p++) {
			if(!finish[p]) { //if process did not finish
				bool canAllocate = true; //if process can be allocated
				for(int r = 0; r<R; r++) {
					if(max[p][r] - alloc[p][r] > work[r]]) {
						canAllocate = false;
						break; //leave entire process if any resouce does not satisfy need
					}
				}

				if(canAllocate) {
					for(int r = 0; r<R; r++) {
						work[r] += alloc[p][r];
					}
					safeSeq[count++] = p;
					finish[p] = true;
					found = true;
				}
			}
		}
		if(!found) return false;
	}

	printf("Safe Sequence: ");
	for(int i = 0; i<P; i++) {
		printf("%d ", safeSeq[i]);	
	}
	printf("\n");

	return true;
}

int main() {

	int noProcesses, noResources;
	printf("Enter the number of processes: ");
	scanf("%d", &noProcesses);
	printf("Enter the number of resources: ");
	scanf("%d", &noResources);

	int available[noResources];

	int max[noProcesses][noResources];
	
	int alloc[noProcesses][noResources];

	printf("Enter the available resources: ");
	for (int i = 0; i < noResources; i++) {
		scanf("%d", &available[i]);	
	}

	printf("Enter the maximum resources: ");
	for (int i = 0; i < noProcesses; i++) {
		for (int j = 0; j < noResources; j++) {	
			scanf("%d", &max[i][j]);
		}
	}

	printf("Enter the allocated resources: ");
	for (int i = 0; i < noProcesses; i++) {
		for (int j = 0; j < noResources; j++) {	
			scanf("%d", &alloc[i][j]);
		}
	}

	if(isSafe(noProcesses, noResources, alloc, max, available)) {
		printf("The system is not in safe state");
	}
	else {
		printf("The system is in safe state");	
	}

	return 0;
}
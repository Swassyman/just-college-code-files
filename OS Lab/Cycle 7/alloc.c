#include<stdio.h>

void resetAlloted(int n, int allotted[]) {
	for(int i = 0; i<n; i++) {
		allotted[i] = 0;
	}
}

void bestfit(int id, int process_size, int n_blocks, int memory[], int allotted[]){ 
	int i, index=-1;
    for (i = 0; i < n_blocks; i++) {  
        if (memory[i] >= process_size && allotted[i]!=1) {                
            if(index == -1) index=i;
            else if(memory[index] > memory[i])
            	index=i;
        }  
    }  
    if (index == -1) {  
        printf("The process %d cannot be allocated\n", id);
        return;
    } 
    else {
    	printf("Process %d was allocated block %d\n", id, index); 
        allotted[index]=1;
        printf("\n"); 
        return;
    } 
} 

void firstfit(int id, int process_size, int n_blocks, int memory[], int allotted[]) { 
	int i;
    for (i = 0; i < n_blocks; i++) {  
        if (memory[i] >= process_size && allotted[i]!=1) {  
            printf("Process %d was allocated block %d\n", id, i); 
            allotted[i]=1;
            printf("\n"); 
            return;
        }  
    }  
    if (i == n_blocks) {  
        printf("The process %d cannot be allocated\n", id);  
        return;
    }  
}

void worstfit(int id, int process_size, int n_blocks, int memory[], int allotted[]) { 
	int i, index=-1;
    for (i = 0; i < n_blocks; i++) {  
        if (memory[i] >= process_size && allotted[i]!=1) {                
            if(index == -1) index=i;
            else if(memory[index] < memory[i])
            	index=i;
        }  
    }  
    if (index == -1) {  
        printf("The process %d cannot be allocated\n", id);  
        return;
    } 
    else {
    	printf("Process %d was allocated block %d\n", id, index); 
        allotted[index]=1;
        printf("\n"); 
        return;
    } 
}

int main() {
	int n_blocks;
	printf("Enter the number of blocks in the system: ");
	scanf("%d", &n_blocks);

	int memory[n_blocks],allotted[n_blocks];

	printf("Enter the size of the different blocks:\n");
	for(int i = 0; i < n_blocks; i++) {
		scanf("%d", &memory[i]);
		allotted[i]=0;
	}

	int n_processes;
	printf("Enter the number of processes in the system: ");
	scanf("%d", &n_processes);
	
	int process[n_processes];
	printf("Enter the size of the different processes:\n");
	for(int i = 0; i < n_blocks; i++) {
		scanf("%d", &process[i]);
	}

	int choice;
	while(1) {
		printf("\nMenu:\n");
		printf("1. First Fit\n");
		printf("2. Best Fit\n");
		printf("3. Worst Fit\n");
		printf("4. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch(choice) {
			case 1:
				resetAlloted(n_blocks, allotted);
				for(int i = 0; i<n_processes; i++) {
					firstfit(i, process[i], n_blocks, memory, allotted);
				}
				break;
			case 2:
				resetAlloted(n_blocks, allotted);
				for(int i = 0; i<n_processes; i++) {
					bestfit(i, process[i], n_blocks, memory, allotted);
				}
				break;
			case 3:
				resetAlloted(n_blocks, allotted);
				for(int i = 0; i<n_processes; i++) {
					worstfit(i, process[i], n_blocks, memory, allotted);
				}
				break;
			case 4:
				return 0;
			default: continue;
		}
	}
}
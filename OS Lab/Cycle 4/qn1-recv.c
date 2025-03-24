#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024
#define MESSAGE_NO 3
#define BUFFER_SIZE 100

typedef struct {
	char message[BUFFER_SIZE];
	int priority;
} Message;

void sort(Message *arr, int n) {
	int i, j;
	Message temp;
	for(i = 0; i < n - 1; i++) {
		for(j = 0; j < n - i - 1; j++) {
			if(arr[j].priority < arr[j + 1].priority) {
				temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
			}
		}
	}
}

int main() {
	key_t key = 2345;
	int shmid;
	Message *sh_mem; //address of shared memory
	
	shmid = shmget(key, sizeof(Message) * MESSAGE_NO, 0666);

	//NULL - System chooses suitable address
	sh_mem = (Message *) shmat(shmid, NULL, 0);

	sort(sh_mem, MESSAGE_NO);

	for (int i = 0; i < MESSAGE_NO; ++i) {
		printf("%s\n", sh_mem[i].message);
	}

	shmdt(sh_mem);
    shmctl(shmid, IPC_RMID, NULL);

	return 0;
}
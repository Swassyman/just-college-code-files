#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

#define BUFFER_SIZE 100
#define MESSAGE_NO 3

typedef struct {
	char message[BUFFER_SIZE];
	int priority;
} Message;

int main() {
	key_t key = 2345;
	int shmid;
	Message * sh_mem; //address of shared memory messages

	shmid = shmget(key, sizeof(Message) * MESSAGE_NO, IPC_CREAT | 0666);
	//NULL - System chooses suitable address
	sh_mem = (Message *) shmat(shmid, NULL, 0);

	for(int i = 0; i<MESSAGE_NO; i++) {
		printf("Enter message: ");
		fgets(sh_mem[i].message, BUFFER_SIZE, stdin);
		sh_mem[i].message[strlen(sh_mem[i].message) - 1] = '\0';
		printf("Enter priority: ");
		scanf("%d", &(sh_mem[i].priority));
		 while(getchar() != '\n');
	}

	return 0;
}
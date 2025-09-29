#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

#define CLASS_SIZE 3

typedef struct {
	char name[20];
	int rollNo;
	int marks;
} Student;

int main() {
	key_t key = 2345;
	int shmid;
	Student * sh_mem; //address of shared memory messages

	shmid = shmget(key, sizeof(Student) * CLASS_SIZE, IPC_CREAT | 0666);
	//NULL - System chooses suitable address
	sh_mem = (Student *) shmat(shmid, NULL, 0);

	for(int i = 0; i<CLASS_SIZE; i++) {
		printf("Enter student %d name: ", i+1);
		fgets(sh_mem[i].name, 20, stdin);
		sh_mem[i].name[strlen(sh_mem[i].name) - 1] = '\0';

		printf("Enter roll no: ");
		scanf("%d", &(sh_mem[i].rollNo));
		while(getchar() != '\n');

		printf("Enter marks: ");
		scanf("%d", &(sh_mem[i].marks));
		 while(getchar() != '\n');
	}

	return 0;
}
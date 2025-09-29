#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024
#define CLASS_SIZE 3

typedef struct {
	char name[20];
	int rollNo;
	int marks;
} Student;

void sort(Student *arr, int n) {
	int i, j;
	Student temp;
	for(i = 0; i < n - 1; i++) {
		for(j = 0; j < n - i - 1; j++) {
			if(arr[j].marks < arr[j + 1].marks) {
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
	Student *sh_mem; //address of shared memory
	
	shmid = shmget(key, sizeof(Student) * CLASS_SIZE, 0666);

	//NULL - System chooses suitable address
	sh_mem = (Student *) shmat(shmid, NULL, 0);

	sort(sh_mem, CLASS_SIZE);

	printf("Roll No\tName\tMarks\n");
	for (int i = 0; i < CLASS_SIZE; ++i) {
		printf("%d\t%s\t%d\n",sh_mem[i].rollNo, sh_mem[i].name, sh_mem[i].marks);
	}

	shmdt(sh_mem);
    shmctl(shmid, IPC_RMID, NULL);

	return 0;
}
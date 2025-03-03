#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int pid = fork();

	if (pid == 0)
	{
		printf("Hello!");
	}

	else if (pid < 0)
	{
		printf("Child function not created!!\n");
		return 1;
	}

	else
	{
		wait(NULL);
		printf("Goodbye");
	}

	printf("\n");
	return 0;
}
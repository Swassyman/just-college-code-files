#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	int x = 100;

	int pid = fork();

	if (pid == 0)
	{
		printf("The value of x in the child process before changing is %d\n", x);
		x=200;
		printf("The value of x in the child process after changing is %d\n", x);
	}

	else if (pid < 0)
	{
		printf("Child function not created!!\n");
		return 1;
	}

	else
	{
		printf("The value of x in the parent process before changing is %d\n", x);
		x=300;
		printf("The value of x in the parent process after changing is %d\n", x);
	}
	printf("\n");
	return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main() {
    int pipefd[2];
    pid_t child1, child2;
    int num1, num2;
    printf("Enter numbers: ");
    scanf("%d %d", &num1, &num2);

    if(pipe(pipefd) == -1) {
        return -1;
    }

    child1 = fork();
    if(child1 == -1) {
        return -1;   
    }
    else if(child1==0) {
        close(pipefd[0]);
        int prod = num1*num2;
        write(pipefd[1], &prod, sizeof(prod));
        close(pipefd[1]);
        exit(EXIT_SUCCESS);
    }

    child2 = fork();
    if(child2 == -1) {
        return -1;
    }
    else if(child2 == 0) {
        close(pipefd[1]);
        int number;
        read(pipefd[0], &number, sizeof(number));
        close(pipefd[0]);
        if(number%2==0) printf("Product is even!\n");
        else printf("Product is odd!\n");
        exit(EXIT_SUCCESS);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);

    printf("Process terminated successfully!\n");
    return 0;

}
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int fd[2];  
    pipe(fd);   

    int pid = fork();

    if (pid == 0) 
    {
        printf("Hello!");
        close(fd[0]);  
        write(fd[1], "Go", 2);  
        close(fd[1]);  
    } 

    else if (pid < 0) 
    {
        printf("Child function not created!!\n");
        return 1;
    } 

    else 
    {  
        char buffer[2];
        close(fd[1]);  
        read(fd[0], &buffer, 2);  
        close(fd[0]); 
        printf("Goodbye");
    }

    printf("\n");
    return 0;
}

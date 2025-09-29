#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    // fork and exec and getpid and wait and exit
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        printf("Child process: PID = %d\n", getpid());
        execlp("/bin/ls", "ls", NULL);
        perror("Exec failed");
        exit(1);
    } else {
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
        wait(NULL);
        printf("Child process finished.\n");
    }

    // Close
    int fd = open("example.txt", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open file");
        return 1;
    }
    printf("File opened successfully. Closing file...\n");
    close(fd);
    printf("File closed.\n");

    // Stat
    struct stat fileStat;
    if (stat("example.txt", &fileStat) < 0) {
        perror("Failed to get file stats");
        return 1;
    }
    printf("File Size: %ld bytes\n", fileStat.st_size);

    // Opendir and Readdir
    DIR *dir;
    struct dirent *entry;
    dir = opendir(".");
    if (dir == NULL) {
        perror("Failed to open directory");
        return 1;
    }
    printf("Contents of the current directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);

    return 0;
}
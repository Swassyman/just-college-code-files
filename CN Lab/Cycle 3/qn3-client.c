#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    fd_set read_fds;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);

    connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Connected to the server. Start chatting!\n");

    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(client_fd, &read_fds);

        select(client_fd + 1, &read_fds, NULL, NULL, NULL);

        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            fgets(buffer, BUFFER_SIZE, stdin);
            send(client_fd, buffer, strlen(buffer), 0);
        }

        if (FD_ISSET(client_fd, &read_fds)) {
            int bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
            buffer[bytes_received] = '\0';
            printf("%s", buffer);
        }
    }
    
    close(client_fd);
    return 0;
}
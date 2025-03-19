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

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server. Start chatting!\n");

    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds); // Add stdin to set
        FD_SET(client_fd, &read_fds);    // Add server socket to set

        if (select(client_fd + 1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("Select failed");
            break;
        }

        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            if (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
                if (send(client_fd, buffer, strlen(buffer), 0) == -1) {
                    perror("Send failed");
                    break;
                }
            }
        }

        if (FD_ISSET(client_fd, &read_fds)) {
            int bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
            if (bytes_received <= 0) {
                printf("Server disconnected.\n");
                break;
            }
            buffer[bytes_received] = '\0';
            printf("%s", buffer);
        }
    }
    
    close(client_fd);
    return 0;
}
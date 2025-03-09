#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

// Function to start the client
void start_client(int part, const char *data) {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Send part number and data to server
    snprintf(buffer, BUFFER_SIZE, "%d %s", part, data);
    sendto(sock_fd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Client sent (Part %d): %s\n", part, data);

    // Receive response from server
    socklen_t addr_len = sizeof(server_addr);
    if (part == 1) {
        recvfrom(sock_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &addr_len);
        printf("Client received (Part %d): %s\n", part, buffer);
    } else if (part == 2) {
        int int_response;
        recvfrom(sock_fd, &int_response, sizeof(int_response), 0, (struct sockaddr *)&server_addr, &addr_len);
        printf("Client received (Part %d): %d\n", part, int_response);
    } else if (part == 3) {
        float float_response;
        recvfrom(sock_fd, &float_response, sizeof(float_response), 0, (struct sockaddr *)&server_addr, &addr_len);
        printf("Client received (Part %d): %.2f\n", part, float_response);
    }

    close(sock_fd);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <part> <data>\n", argv[0]);
        return 1;
    }

    int part = atoi(argv[1]);
    const char *data = argv[2];

    start_client(part, data);

    return 0;
}
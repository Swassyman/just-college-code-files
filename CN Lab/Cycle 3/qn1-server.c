#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

void calculate_stats(int *arr, int n, int *max, int *min, float *avg) {
    *max = *min = arr[0];
    *avg = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] > *max) *max = arr[i];
        if (arr[i] < *min) *min = arr[i];
        *avg += arr[i];
    }

    *avg /= n;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        read(new_socket, buffer, BUFFER_SIZE);
        int n = atoi(strtok(buffer, ","));
        int arr[n];
        for (int i = 0; i < n; i++) {
            arr[i] = atoi(strtok(NULL, ","));
        }

        int max, min;
        float avg;
        calculate_stats(arr, n, &max, &min, &avg);

        char response[BUFFER_SIZE];
        snprintf(response, BUFFER_SIZE, "Max: %d, Min: %d, Avg: %.2f", max, min, avg);
        send(new_socket, response, strlen(response), 0);
        printf("Response sent: %s\n", response);

        close(new_socket);
    }

    close(server_fd);
    return 0;
}
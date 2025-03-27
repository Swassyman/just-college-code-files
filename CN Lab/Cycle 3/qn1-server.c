#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12345
#define BUFFER_SIZE 1024

void calculateStats(int arr[], int n, int *max, int *min, float *avg) {
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
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address, client_address;
    socklen_t addrlen = sizeof(client_address);
    
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address));
    listen(server_fd, 4);

    while (1) {
        int client_fd = accept(server_fd, (struct sockaddr *)&client_address, &addrlen);

        char buffer[BUFFER_SIZE];
        recv(client_fd, buffer, BUFFER_SIZE, 0);

        int n;
        memcpy(&n, buffer, sizeof(int));

        int arr[n];
        memcpy(arr, buffer + sizeof(int), n * sizeof(int));

        int max, min;
        float avg;
        calculateStats(arr, n, &max, &min, &avg);

        char response[BUFFER_SIZE];
        snprintf(response, BUFFER_SIZE, "Max: %d, Min: %d, Avg: %.2f", max, min, avg);
        send(client_fd, response, strlen(response), 0);

        close(client_fd);
    }

    close(server_fd);
    return 0;
}

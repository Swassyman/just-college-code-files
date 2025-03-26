#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12345
#define BUFFER_SIZE 1024

void calculateStats(int arr[], int n, int *max, int *min, float *avg) {
    *max = arr[0];
    *min = arr[0];
    *avg = 0;

    for(int i = 0; i<n; i++) {
        if(arr[i] > *max) *max = arr[i];
        if(arr[i] < *min) *min = arr[i];
        *avg += arr[i];
    }
    *avg /= n;
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int buffer[BUFFER_SIZE];

    struct sockaddr_in address;
    int addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    listen(server_fd, 4);

    printf("Server listening\n");

    while(1) {
        int client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

        int buffer[BUFFER_SIZE];
        read(client_fd, buffer, BUFFER_SIZE);
        

        printf("%d", buffer[0]);
        int n = buffer[0];
        int arr[n];

        for(int i = 1; i < n + 1; i++) {
            arr[i - 1] = buffer[i];
        }
        int max, min;
        float avg;
        calculateStats(arr, n, &max, &min, &avg);

        char response[BUFFER_SIZE];
        snprintf(response, BUFFER_SIZE, "Max: %d, Min: %d, Avg: %.2f", max, min, avg);
        send(client_fd, response, BUFFER_SIZE, 0);

        close(client_fd);
    }

    close(server_fd);
    return 0;
}


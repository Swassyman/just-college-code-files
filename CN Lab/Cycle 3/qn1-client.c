#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    connect(client_fd, (struct sockaddr *)&server_address, sizeof(server_address));

    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);

    char data[BUFFER_SIZE];
    memcpy(data, &n, sizeof(n));
    memcpy(data + sizeof(n), arr, sizeof(arr));

    send(client_fd, data, sizeof(n) + sizeof(arr), 0);

    char response[BUFFER_SIZE] = {0};
    read(client_fd, response, BUFFER_SIZE);
    printf("%s\n", response);

    close(client_fd);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    int addrlen = sizeof(server_address);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    connect(client_fd, (struct sockaddr *)&server_address, addrlen);

    int arr[] = { 10, 20, 30, 40, 50};
    int n = sizeof(arr)/sizeof(arr[0]);

    char data[BUFFER_SIZE];
    data[0] = n;
    for(int i = 0; i < n; i++) {
        data[i+1] = arr[i];
    }

    send(client_fd, data, BUFFER_SIZE, 0);
    printf("Array sent to server: ");

    char buffer[BUFFER_SIZE];
    read(client_fd, buffer, BUFFER_SIZE);
    printf("%s\n", buffer);



    return 0;
}
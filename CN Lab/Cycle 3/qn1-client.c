#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); //converting port to network byte order

    //converts ip address to binary format and stores it in sin_addr
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    char data[BUFFER_SIZE];
    //first element has size of array
    snprintf(data, BUFFER_SIZE, "%d", n);
    for (int i = 0; i < n; i++) {
        char temp[10];
        snprintf(temp, 10, ",%d", arr[i]); //writes to a char buffer
        strcat(data, temp);
    }

    send(sock, data, strlen(data), 0);
    printf("Array sent to server\n");

    read(sock, buffer, BUFFER_SIZE);
    printf("Server response: %s\n", buffer);

    close(sock);
    return 0;
}
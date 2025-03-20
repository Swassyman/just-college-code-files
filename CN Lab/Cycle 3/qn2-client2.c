#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    int number;
    float result;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(12345);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(sock);
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    char data_type;
    read(sock, &data_type, sizeof(data_type));

    if (data_type == 's') {
        int bytes_read = read(sock, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("Reversed string: %s\n", buffer);
        }
    } else if (data_type == 'i') {
        if (read(sock, &number, sizeof(number)) > 0) {
            printf("Squared number: %d\n", number);
        }
    } else if (data_type == 'f') {
        if (read(sock, &result, sizeof(result)) > 0) {
            printf("Adjusted value: %f\n", result);
        }
    }

    close(sock);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <math.h>

void reverse_string(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

int main() {
    int server_fd, client1_fd, client2_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    int number;
    float float_number;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(12345);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 2) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server waiting for connections...\n");

    if ((client1_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Connected to Client 1\n");

    if ((client2_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Connected to Client 2\n");

    char data_type;
    read(client1_fd, &data_type, sizeof(data_type));

    if (data_type == 's') {
        read(client1_fd, buffer, 1024);
        printf("Received: %s\n", buffer);

        reverse_string(buffer);

        send(client2_fd, &data_type, sizeof(data_type), 0);
        send(client2_fd, buffer, strlen(buffer), 0);
        printf("Sent: %s\n", buffer);

    } else if (data_type == 'i') {
        read(client1_fd, &number, sizeof(number));
        printf("Received: %d, Sent: %d\n", number, number * number);

        number = number * number;

        send(client2_fd, &data_type, sizeof(data_type), 0);
        send(client2_fd, &number, sizeof(number), 0);
        printf("Sent: %d\n", number);

    } else if (data_type == 'f') {
        read(client1_fd, &float_number, sizeof(float_number));
        printf("Received: %f\n", float_number);

        float result = pow(float_number, 1.5);
        printf("Received: %f, Sent: %f\n", float_number, result);

        send(client2_fd, &data_type, sizeof(data_type), 0);
        send(client2_fd, &result, sizeof(result), 0);
        printf("Sent: %f\n", result);

    }
    
    close(client1_fd);
    close(client2_fd);
    close(server_fd);
    return 0;
}
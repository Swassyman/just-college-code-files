#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char data_type = 'i'; // Change to 'i' or 'f' for other parts
    char *message = "Hello, World!";
    int number = 5;
    float float_number = 4.0;

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

    send(sock, &data_type, sizeof(data_type), 0);

    if (data_type == 's') {
        send(sock, message, strlen(message), 0);
        printf("Message sent: %s\n", message);
    } else if (data_type == 'i') {
        send(sock, &number, sizeof(number), 0);
        printf("Number sent: %d\n", number);
    } else if (data_type == 'f') {
        send(sock, &float_number, sizeof(float_number), 0);
        printf("Float number sent: %f\n", float_number);
    }

    close(sock);
    return 0;
}
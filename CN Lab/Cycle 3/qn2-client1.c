#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char data_type = 'i';  // Change as needed
    char message[] = "Hello, World!";
    int number = 5;
    float float_number = 4.0;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(12345);
    serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    send(sock, &data_type, sizeof(data_type), 0);

    switch (data_type) {
        case 's':
            send(sock, message, strlen(message), 0);
            printf("Message sent: %s\n", message);
            break;
        case 'i':
            send(sock, &number, sizeof(number), 0);
            printf("Number sent: %d\n", number);
            break;
        case 'f':
            send(sock, &float_number, sizeof(float_number), 0);
            printf("Float number sent: %f\n", float_number);
            break;
    }

    close(sock);
    return 0;
}

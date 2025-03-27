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
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = {0};
    int number;
    float float_number;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(12345);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));

    listen(server_fd, 2);
    printf("Server waiting for connections...\n");

    while (1) {
        if ((client1_fd = accept(server_fd, (struct sockaddr*)&address, &addrlen)))
            printf("Connected to client 1\n");
        if ((client2_fd = accept(server_fd, (struct sockaddr*)&address, &addrlen)))
            printf("Connected to client 2\n");

        char data_type;
        read(client1_fd, &data_type, sizeof(data_type));

        switch (data_type) {
            case 's': {
                send(client2_fd, &data_type, sizeof(data_type), 0);
                int bytes_read = read(client1_fd, buffer, sizeof(buffer) - 1);
                buffer[bytes_read] = '\0';
                printf("Received: %s\n", buffer);
                reverse_string(buffer);
                send(client2_fd, buffer, strlen(buffer), 0);
                printf("Sent: %s\n", buffer);
                break;
            }

            case 'i': {
                send(client2_fd, &data_type, sizeof(data_type), 0);
                read(client1_fd, &number, sizeof(number));
                printf("Received: %d\n", number);
                number *= number;
                send(client2_fd, &number, sizeof(number), 0);
                printf("Sent: %d\n", number);
                break;
            }

            case 'f': {
                send(client2_fd, &data_type, sizeof(data_type), 0);                
                read(client1_fd, &float_number, sizeof(float_number));
                float result = pow(float_number, 1.5);
                printf("Received: %f, Sent: %f\n", float_number, result);
                send(client2_fd, &result, sizeof(result), 0);
                break;
            }
            default:
                break;
        }

        close(client1_fd);
        close(client2_fd);
    }

    close(server_fd);
    return 0;
}

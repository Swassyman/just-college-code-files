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

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(12345);
    serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    char data_type;
    read(sock, &data_type, sizeof(data_type));

    switch (data_type) {
        case 's': {
            int bytes_read = read(sock, buffer, sizeof(buffer));
            buffer[bytes_read] = '\0';
            printf("Reversed string: %s\n", buffer);
            break;
        }
        case 'i':
            read(sock, &number, sizeof(number));
            printf("Squared number: %d\n", number);
            break;
        case 'f':
            read(sock, &result, sizeof(result));
            printf("Processed float: %f\n", result);
            break;
    }

    close(sock);
    return 0;
}

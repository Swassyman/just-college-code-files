#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define UDP_PORT 9090
#define FLOAT_PORT 7070
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

void send_tcp_message(const char *message) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    send(sock, message, strlen(message), 0);
    recv(sock, buffer, BUFFER_SIZE, 0);
    printf("Reversed String: %s\n", buffer);
    close(sock);
}

void send_udp_message(int number) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(UDP_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    sprintf(buffer, "%d", number);
    sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    recvfrom(sock, buffer, BUFFER_SIZE, 0, NULL, NULL);
    printf("Squared Number: %s\n", buffer);
    close(sock);
}

void send_float_message(float number) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(FLOAT_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    sprintf(buffer, "%.2f", number);
    sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    recvfrom(sock, buffer, BUFFER_SIZE, 0, NULL, NULL);
    printf("Processed Float: %s\n", buffer);
    close(sock);
}

int main() {
    send_tcp_message("hello");
    send_udp_message(4);
    send_float_message(2.5);
    return 0;
}

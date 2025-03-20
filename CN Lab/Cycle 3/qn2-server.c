#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <math.h>

#define PORT 8080
#define UDP_PORT 9090
#define FLOAT_PORT 7070
#define BUFFER_SIZE 1024

void handle_tcp_connection(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received <= 0) return;
    buffer[bytes_received] = '\0';

    int len = strlen(buffer);
    for (int i = 0; i < len / 2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[len - i - 1];
        buffer[len - i - 1] = temp;
    }
    
    send(client_socket, buffer, strlen(buffer), 0);
    close(client_socket);
}

void handle_udp_connection() {
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in udp_server_addr, udp_client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(udp_client_addr);

    udp_server_addr.sin_family = AF_INET;
    udp_server_addr.sin_addr.s_addr = INADDR_ANY;
    udp_server_addr.sin_port = htons(UDP_PORT);

    bind(udp_socket, (struct sockaddr *)&udp_server_addr, sizeof(udp_server_addr));
    recvfrom(udp_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&udp_client_addr, &addr_len);
    
    int num = atoi(buffer);
    num *= num;
    sprintf(buffer, "%d", num);
    
    sendto(udp_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&udp_client_addr, addr_len);
    close(udp_socket);
}

void handle_float_connection() {
    int float_socket = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in float_server_addr, float_client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(float_client_addr);

    float_server_addr.sin_family = AF_INET;
    float_server_addr.sin_addr.s_addr = INADDR_ANY;
    float_server_addr.sin_port = htons(FLOAT_PORT);

    bind(float_socket, (struct sockaddr *)&float_server_addr, sizeof(float_server_addr));
    recvfrom(float_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&float_client_addr, &addr_len);
    
    float num = atof(buffer);
    float result = pow(num, 1.5);
    sprintf(buffer, "%.2f", result);
    
    sendto(float_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&float_client_addr, addr_len);
    close(float_socket);
}

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);

    if (fork() == 0) handle_udp_connection();
    if (fork() == 0) handle_float_connection();

    while (1) {
        int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
        if (fork() == 0) {
            handle_tcp_connection(client_socket);
            exit(0);
        }
        close(client_socket);
    }
    close(server_socket);
}
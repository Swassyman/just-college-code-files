#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <math.h>

#define PORT 12345
#define BUFFER_SIZE 1024

void reverse_string(char *str);
void handle_part_a(char *data, char *response);
void handle_part_b(int data, int *response);
void handle_part_c(float data, float *response);

void reverse_string(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

void handle_part_a(char *data, char *response) {
    strcpy(response, data);
    reverse_string(response);
}

void handle_part_b(int data, int *response) {
    *response = data * data;
}

void handle_part_c(float data, float *response) {
    *response = pow(data, 1.5);
}

void start_server() {
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server started and listening on port %d...\n", PORT);

    while (1) {
        int bytes_received = recvfrom(server_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        if (bytes_received < 0) {
            perror("Receive failed");
            continue;
        }

        int part;
        char data[BUFFER_SIZE];
        sscanf(buffer, "%d %s", &part, data);

        char response[BUFFER_SIZE];
        int int_response;
        float float_response;

        switch (part) {
            case 1:
                handle_part_a(data, response);
                printf("Server received (Part a): %s\n", data);
                printf("Server sent (Part a): %s\n", response);
                sendto(server_fd, response, strlen(response), 0, (struct sockaddr *)&client_addr, addr_len);
                break;

            case 2:
                handle_part_b(atoi(data), &int_response);
                printf("Server received (Part b): %d\n", atoi(data));
                printf("Server sent (Part b): %d\n", int_response);
                sendto(server_fd, &int_response, sizeof(int_response), 0, (struct sockaddr *)&client_addr, addr_len);
                break;

            case 3:
                handle_part_c(atof(data), &float_response);
                printf("Server received (Part c): %.2f\n", atof(data));
                printf("Server sent (Part c): %.2f\n", float_response);
                sendto(server_fd, &float_response, sizeof(float_response), 0, (struct sockaddr *)&client_addr, addr_len);
                break;

            default:
                printf("Invalid part number received\n");
                break;
        }
    }

    close(server_fd);
}

int main() {
    start_server();
    return 0;
}
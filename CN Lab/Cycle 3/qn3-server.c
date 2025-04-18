#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024
#define PORT 12345

int clients[MAX_CLIENTS];
int n_clients = 0;

void broadcast_message(int sender_fd, const char *message) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] != -1 && clients[i] != sender_fd) {
            send(clients[i], message, strlen(message), 0);
        }
    }
}

void add_client(int client_fd) {
    if (n_clients < MAX_CLIENTS) {
        clients[n_clients++] = client_fd;
        printf("New client connected. Total clients: %d\n", n_clients);
    } else {
        printf("Max clients reached. Connection rejected.\n");
        close(client_fd);
    }
}

void remove_client(int client_fd) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] == client_fd) {
            clients[i] = -1;
            n_clients--;
            printf("Client disconnected. Total clients: %d\n", n_clients);
            break;
        }
    }
    close(client_fd);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    fd_set read_fds;
    int max_fd;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        clients[i] = -1;
    }

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    listen(server_fd, 5);

    printf("Server started on port 12345. Waiting for connections...\n");

    while (1) {
        //Clear read FD
        FD_ZERO(&read_fds);
        
        FD_SET(server_fd, &read_fds);
        max_fd = server_fd;

        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i] != -1) {
                FD_SET(clients[i], &read_fds);
                if (clients[i] > max_fd) {
                    max_fd = clients[i];
                }
            }
        }

        select(max_fd + 1, &read_fds, NULL, NULL, NULL);

        if (FD_ISSET(server_fd, &read_fds)) {
            client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
            add_client(client_fd);
        }

        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i] != -1 && FD_ISSET(clients[i], &read_fds)) {
                int bytes_received = recv(clients[i], buffer, BUFFER_SIZE, 0);
                if (bytes_received <= 0) {
                    printf("Client %d disconnected.\n", clients[i]);
                    remove_client(clients[i]);
                } else {
                    buffer[bytes_received] = '\0';
                    broadcast_message(clients[i], buffer);
                }
            }
        }
    }

    close(server_fd);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <string.h>
#include <unistd.h>

int main() {
    int client = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);

    connect(client, (struct sockaddr *)&server_addr, sizeof(server_addr));

    char message[1024];

    while (1) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        FD_SET(client, &fds);
        int max_fd = (STDIN_FILENO > client) ? STDIN_FILENO : client;

        select(max_fd + 1, &fds, NULL, NULL, NULL);

        if (FD_ISSET(STDIN_FILENO, &fds)) {
            fgets(message, sizeof(message), stdin);
            message[strcspn(message, "\n")] = 0;
            send(client, message, strlen(message) + 1, 0);
        }

        if (FD_ISSET(client, &fds)) {
            int len = recv(client, message, sizeof(message), 0);
            if (len <= 0) {
                printf("Disconnected!\n");
                break;
            }
            printf("%s\n", message);
        }
    }

    close(client);
    return 0;
}

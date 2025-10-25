#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>

int clients[10];
int n_clients = 0;
char message[100];

void add_client(int client){
    if(n_clients >= 10) {
        printf("Maximum number of clients bruh");
        close(client);
    }
    else {
        clients[n_clients++] = client;
    }
}

void remove_client(int client){
    for(int i = 0; i < 10; i++){
        if(clients[i] == client){
            clients[i] = -1;
            n_clients--;
            break;
        }
    }
    close(client);  
}

void broadcast_message(int sender, char buffer[]){
    for(int i = 0; i<10; i++){
        if(clients[i]!=-1 && clients[i]!=sender){
            send(clients[i], buffer, sizeof(message), 0);
        }
    }
}

int main() {
    int server, client;
    fd_set fds;
    
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_size = sizeof(client_addr);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);

    server = socket(AF_INET, SOCK_STREAM, 0);

    for(int i = 0 ; i<10; i++){
        clients[i] = -1;
    }

    bind(server, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server, 10);

    while(1){
        FD_ZERO(&fds);
        FD_SET(server, &fds);

        int max_fd = server;

        for(int i = 0; i<10; i++){
            if(clients[i]!=-1){
                FD_SET(clients[i], &fds);
                if(clients[i] > max_fd) max_fd = clients[i];
            }
        }

        select(max_fd + 1, &fds, NULL, NULL, NULL);

        if(FD_ISSET(server, &fds)){
            client = accept(server, (struct sockaddr *)&client_addr, &client_size);
            add_client(client);
        }

        for(int i = 0; i<10; i++){
            if(clients[i]!=-1 && FD_ISSET(clients[i], &fds)){
                int len = recv(clients[i], message, sizeof(message), 0);
                if(len == 0){
                    remove_client(clients[i]);  
                }
                else {
                    broadcast_message(clients[i], message);
                }
            }
        }
    }
}

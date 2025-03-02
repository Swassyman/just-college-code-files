#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
	int client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if( client_fd < 0) {
		printf("Error in connection.\n");
		return -1;
	}

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);

	if(inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
		printf("Invalid address.\n");
		close(client_fd);
		return -1;
	}
	
	if (connect(client_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
		printf("Connection Failed.\n");
		close(client_fd);
		return -1;
	}

	char *message = "Hello! This is Client ;P";
	send(client_fd, message, strlen(message), 0);

	char buffer[BUFFER_SIZE];
	int bytes_received = read(client_fd, buffer, BUFFER_SIZE);
	if(bytes_received < 0) {
		printf("Error in receiving data.\n");
		close(client_fd);
		return -1;
	}

	printf("Received data: %s\n", buffer);
	close(client_fd);
}
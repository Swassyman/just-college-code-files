#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#define BUFFER_SIZE 1024
#define PORT 8080

int main(){
	int server_fd = socket(AF_INET, SOCK_STREAM, 0); //creating a socket
	if (server_fd==-1) {
		printf("Socket Creation Failed\n");
		return -1;
	}

	struct sockaddr_in server_address; //defining server adddress
	server_address.sin_family = AF_INET; //address family for server (afinet for ipv4)
	server_address.sin_addr.s_addr = INADDR_ANY; //ip address - inaddr_any means any available ip
	server_address.sin_port = htons(PORT); //port number converted to network byte order using htons

	if( bind(server_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0 ) {
		printf("Bind Failed\n");
		close(server_fd);
		return -1;
	}
	if( listen(server_fd, 5) < 0) {
		printf("Listen Failed\n");
		close(server_fd);
		return -1;
	}

	int client_fd;
	struct sockaddr_in client_address;
	socklen_t client_address_size = sizeof(client_address);
	client_fd = accept(server_fd, (struct sockaddr*)&client_address, &client_address_size);
	if( client_fd < 0) {
		printf("Accept Failed\n");
		close(server_fd);
		return -1;
	}

	char buffer[BUFFER_SIZE];
	int bytes_read = read(client_fd, buffer, BUFFER_SIZE);
	if( bytes_read < 0 ) {
		printf("Read Failed\n");
		close(client_fd);
		close(server_fd);
		return -1;
	}

	printf("Received: %s\n", buffer);
	char *response = "Hello! This is Server :D";
	write(client_fd, response, strlen(response));
	close(client_fd);
	close(server_fd);
	return 1;
}
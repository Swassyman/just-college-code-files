#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#define BUFFER_SIZE 1024
#define PORT 8080

int main(){
	int server_fd = socket(AF_INET, SOCK_DGRAM, 0); //creating a socket
	if (server_fd==-1) {
		printf("Socket Creation Failed\n");
		return -1;
	}

	struct sockaddr_in server_address, client_address; //defining server adddress
	server_address.sin_family = AF_INET; //address family for server (afinet for ipv4)
	server_address.sin_addr.s_addr = INADDR_ANY; //ip address - inaddr_any means any available ip
	server_address.sin_port = htons(PORT); //port number converted to network byte order using htons
	socklen_t client_address_size = sizeof(client_address);

	if( bind(server_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0 ) {
		printf("Bind Failed\n");
		close(server_fd);
		return -1;
	}

	printf("UDP is open to listening on port: %d\n",PORT);
	char buffer[BUFFER_SIZE];

	while(1) {
		int bytes_read = recvfrom(server_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_address, &client_address_size);
		if(bytes_read < 0) {
			printf("Read Failed\n");
			close(server_fd);
			return -1;
		}
		buffer[bytes_read] = '\0';
		printf("Received: %s\n", buffer);

		char *response = "Hewo! Client here!";
		if(sendto(server_fd, response, strlen(response), 0, (struct sockaddr *)&client_address, client_address_size) < 0) {
			printf("Write Failed\n");
			close(server_fd);
			return -1;
		}
		printf("Message sent to client\n");
	}
	close(server_fd);
	return 1;
}
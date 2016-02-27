#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	//declaration of variables
	double num1, num2, sum;
	int op;
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	//creating my socket and using datagram to connect with ip and port address
	unlink("server_socket");
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_port = htons(9734);
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *) &server_address, server_len);
	
	listen(server_sockfd,10 );
	while(1)
	{
		
		printf("\nServer waiting for a client...\n");
		
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, &client_len);
		
		read(client_sockfd, &num1, 8);
		read(client_sockfd, &num2, 8);
		read(client_sockfd, &op, 1);
		
		printf("The following %.2f %c %.2f was received from client\n", num1,op, num2);
		//i have recieved my operation as an integer trying to test to its corresponding char
		switch(op){
			case 43:
				sum = num1 + num2;
				break;
			case 42:
				sum = num1 * num2;
				break;
			case 45:
				sum = num1 - num2;
				break;
			case 47:
				sum = num1 / num2;
				break;
			case 37:
				//sum = num1 % num2;
				break;
			default:
				printf("client enter invalid operation\n");
				return 0;
				break;
			}
		printf("the result is %.2f\n", sum);
		write(client_sockfd, &sum, 8);
		close(client_sockfd);
	}
		
	return 0;
}

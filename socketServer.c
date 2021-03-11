#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
int main()
{
	int sockfd;
	sockfd = socket(AF_INET ,SOCK_STREAM, IPPROTO_TCP);
	//Socket created successfully
	printf("Socket created successfully!\n");
	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(10086);
	int r = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if (-1 == r)
	{
		printf("bind failed!\n");
		return -2;
	}
	//Binding socket succeeded
	printf("Binding socket succeeded!\n");
	int c = listen(sockfd, 10);
	if (-1 == r)
	{
		printf("listen failed!\n");
		return -2;
	}	
	//Listening socket succeeded
	printf("Listening socket succeeded!\n");
	int clientSocket;
	struct sockaddr_in addc = {0};
	int len = sizeof(addc);
	printf("Waiting for someone to connect the server...\n");
	clientSocket = accept(sockfd, (struct sockaddr*)&addc, &len);
	if(clientSocket == SO_ERROR)
	{
		printf("Server down！\n");
		return -2;
	}
	printf("someone connects to the server!\n");
	//now we can communicate with each other
	char buff[1024];
	while(1)
	{
		c = recv(clientSocket, buff, 1023, 0);
		if(r > 0)
		{
			buff[c] = 0;
			printf(">>%s\n",buff);
		}
	}	
	return 0;
}

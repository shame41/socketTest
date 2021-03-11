#include<stdio.h>
#include<Windows.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	//第一步,请求协议版本
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);
	if(LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion)!=2)
	{
		printf("请求协议失败！\n");
		return -1;
	}
	//第二步,创建socket
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == serverSocket)
	{
		printf("创建socket失败!\n");
		WSACleanup();
		return -2;
	}
	//第三步,创建协议地址族
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;//协议版本
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.5.1");
	addr.sin_port = htons(10086);
	//第四步,绑定
	int r = bind(serverSocket, (sockaddr*)&addr, sizeof addr);
	if (-1 == r)
	{
		printf("bind失败！\n");
		closesocket(serverSocket);
		WSACleanup();
		return -2;
	}
	//第五步，监听
	r = listen(serverSocket, 10);
	if (-1 == r)
	{
		printf("监听失败！\n");
		closesocket(serverSocket);
		WSACleanup();
		return -2;
	}
	//第六步，等待客户端连接
	SOCKADDR_IN cAddr = { 0 };
	int len = sizeof cAddr;
	SOCKET clientSocket = accept(serverSocket, (sockaddr*)&cAddr, &len);
	if (SOCKET_ERROR == clientSocket )
	{
		printf("服务器宕机了！\n");
		closesocket(serverSocket);
		WSACleanup();
		return -2;
	}
	printf("有客户端连接到服务器了：%s!\n", inet_ntoa(cAddr.sin_addr));
	//第七步,通信
	char buff[1024];
	while (1)
	{
		r = recv(clientSocket, buff, 1023, NULL);
		if (r > 0)
		{
			buff[r] = 0;//结尾'\0'
			printf(">>%s\n", buff);
		}
	}
	getchar();
	return 0;
}

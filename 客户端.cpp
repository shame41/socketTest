#include<stdio.h>
#include<Windows.h>
#include<string.h>
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
	printf("请求协议成功！\n");
	//第二步,创建socket
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == clientSocket)
	{
		printf("创建socket失败!\n");
		WSACleanup();
		return -2;
	}
	printf("创建socket成功\n");
	//第三步,获取服务器协议地址族
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;//协议版本
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.5.1");
	addr.sin_port = htons(10086);
	printf("获取服务器协议地址族成功\n");
	//第四步,连接服务器
	int r = connect(clientSocket, (sockaddr*)&addr, sizeof addr);
	if (r == -1)
	{
		printf("连接服务器失败！\n");
		return -1;
	}
	printf("连接服务器成功！\n");	
	//第五步,通信
	char buff[1024];
	while (1)
	{
		memset(buff, 0, 1024);
		printf("请输入内容：");
		scanf("%s", buff);
		r = send(clientSocket, buff, strlen(buff), NULL);
	}
	return 0;
}
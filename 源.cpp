#include<stdio.h>
#include<Windows.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	//��һ��,����Э��汾
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);
	if(LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion)!=2)
	{
		printf("����Э��ʧ�ܣ�\n");
		return -1;
	}
	//�ڶ���,����socket
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == serverSocket)
	{
		printf("����socketʧ��!\n");
		WSACleanup();
		return -2;
	}
	//������,����Э���ַ��
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;//Э��汾
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.5.1");
	addr.sin_port = htons(10086);
	//���Ĳ�,��
	int r = bind(serverSocket, (sockaddr*)&addr, sizeof addr);
	if (-1 == r)
	{
		printf("bindʧ�ܣ�\n");
		closesocket(serverSocket);
		WSACleanup();
		return -2;
	}
	//���岽������
	r = listen(serverSocket, 10);
	if (-1 == r)
	{
		printf("����ʧ�ܣ�\n");
		closesocket(serverSocket);
		WSACleanup();
		return -2;
	}
	//���������ȴ��ͻ�������
	SOCKADDR_IN cAddr = { 0 };
	int len = sizeof cAddr;
	SOCKET clientSocket = accept(serverSocket, (sockaddr*)&cAddr, &len);
	if (SOCKET_ERROR == clientSocket )
	{
		printf("������崻��ˣ�\n");
		closesocket(serverSocket);
		WSACleanup();
		return -2;
	}
	printf("�пͻ������ӵ��������ˣ�%s!\n", inet_ntoa(cAddr.sin_addr));
	//���߲�,ͨ��
	char buff[1024];
	while (1)
	{
		r = recv(clientSocket, buff, 1023, NULL);
		if (r > 0)
		{
			buff[r] = 0;//��β'\0'
			printf(">>%s\n", buff);
		}
	}
	getchar();
	return 0;
}

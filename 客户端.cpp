#include<stdio.h>
#include<Windows.h>
#include<string.h>
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
	printf("����Э��ɹ���\n");
	//�ڶ���,����socket
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == clientSocket)
	{
		printf("����socketʧ��!\n");
		WSACleanup();
		return -2;
	}
	printf("����socket�ɹ�\n");
	//������,��ȡ������Э���ַ��
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;//Э��汾
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.5.1");
	addr.sin_port = htons(10086);
	printf("��ȡ������Э���ַ��ɹ�\n");
	//���Ĳ�,���ӷ�����
	int r = connect(clientSocket, (sockaddr*)&addr, sizeof addr);
	if (r == -1)
	{
		printf("���ӷ�����ʧ�ܣ�\n");
		return -1;
	}
	printf("���ӷ������ɹ���\n");	
	//���岽,ͨ��
	char buff[1024];
	while (1)
	{
		memset(buff, 0, 1024);
		printf("���������ݣ�");
		scanf("%s", buff);
		r = send(clientSocket, buff, strlen(buff), NULL);
	}
	return 0;
}
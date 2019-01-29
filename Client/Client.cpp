#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <WinSock2.h>

using namespace std;

void ShowErrorMessage(string messge)
{
	cout << "[Error] :" << messge << "\n";
	system("pause");
	exit(1);
}

int main()
{
	WSADATA WsaData;
	SOCKET ClientSocket;
	SOCKADDR_IN ServerAddress;

	int Server_Port = 9874;
	char received[256];
	string sent;

	if (WSAStartup(MAKEWORD(2, 2), &WsaData) != 0) //winsock �ʱ�ȭ makeword(2,2)���� ���
		ShowErrorMessage("WSAStartip()");

	ClientSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (ClientSocket == INVALID_SOCKET)
		ShowErrorMessage("socket()");

	memset(&ServerAddress, 0, sizeof(ServerAddress));
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerAddress.sin_port = htons(Server_Port);
	if (connect(ClientSocket, (SOCKADDR*)&ServerAddress, sizeof(ServerAddress)) == SOCKET_ERROR)
		ShowErrorMessage("connect()\n");
	cout << "[���� ����] connect()\n";

	while (1){
		cout << "[�޽��� ����]: ";
		getline(cin, sent);
		if (sent == "") continue;
		send(ClientSocket, sent.c_str(), sent.length(), 0);
		int length = recv(ClientSocket, received, sizeof(received), 0);
		received[length] = '\0';
		if (strcmp(received, "[exit]") == 0){
			cout << "[���� ����]\n";
			break;
		}
		cout << "[���� �޽���]: " << received << '\n';
	}
	closesocket(ClientSocket);
	WSACleanup();
	system("pause");
	return 0;


}
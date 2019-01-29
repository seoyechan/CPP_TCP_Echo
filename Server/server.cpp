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
	SOCKET ServerSocket, ClientSocket;
	SOCKADDR_IN ServerAddress, ClientAddress;

	int Server_Port = 9874;
	char receive[256]; //주고 받을 때 문자열 버퍼

	if (WSAStartup(MAKEWORD(2, 2), &WsaData) != 0) //winsock 초기화 makeword(2,2)버전 사용
		ShowErrorMessage("WSAStartip()");

	ServerSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (ServerSocket == INVALID_SOCKET)
		ShowErrorMessage("socket()");

	memset(&ServerAddress, 0, sizeof(ServerAddress));
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	ServerAddress.sin_port = htons(Server_Port);
	if (bind(ServerSocket, (SOCKADDR*)&ServerAddress, sizeof(ServerAddress)) == SOCKET_ERROR)
		ShowErrorMessage("bind()\n");
	cout << "[현재 상태] bind()\n";

	if (listen(ServerSocket, 5) == SOCKET_ERROR)
		ShowErrorMessage("listen()");
	cout << "[현재 상태] listen()\n";

	int SizeClientAddress = sizeof(ClientAddress);
	ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddress, &SizeClientAddress);
	cout << "[현재 상태] accept()\n";

	if (ClientSocket == INVALID_SOCKET)
		ShowErrorMessage("accept()");
	while (1){
		int length = recv(ClientSocket, receive, sizeof(receive), 0);
		receive[length] = NULL;
		cout << "[클라이언트 메시지]" << receive << "\n";
		cout << "[메시지 전송]: " << receive << "]\n";
		if (strcmp(receive, "[exit]") == 0){
			send(ClientSocket, receive, sizeof(receive) - 1, 0);
			cout << "[서버 종료]\n";
			break;
		}
		send(ClientSocket, receive, sizeof(receive) - 1, 0);
	}

	closesocket(ClientSocket);
	closesocket(ServerSocket);
	WSACleanup();
	system("pause");
	return 0;



}
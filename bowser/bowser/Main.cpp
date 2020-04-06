#include <winsock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <iostream>
#include "Client.h"
#pragma comment(lib,"ws2_32.lib")
using namespace std;
int main() 
{
	// Initialize Dependencies to the Windows Socket.
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "WSAStartup failed.\n";
		system("pause");
		return -1;
	}

	Client* myClient = new Client("www.google.com");
	myClient->sendbytes();

	WSACleanup();
	system("pause");
	return 0;
}
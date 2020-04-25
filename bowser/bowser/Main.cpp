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

	string site = "";

	cout << "Enter the website you want to send a GET request to: ";
	cin >> site;

	Client* myClient = new Client(site);
	Payload* pl = myClient->doGet();
	pl->print();

	WSACleanup();
	return 0;
}
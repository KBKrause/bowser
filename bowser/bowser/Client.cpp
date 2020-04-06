#include "Client.h"

Client::Client(std::string uri)
{
	// We first prepare some "hints" for the "getaddrinfo" function
	// to tell it, that we are looking for a IPv4 TCP Connection.
	SecureZeroMemory(&(this->hints), sizeof(this->hints));
	hints.ai_family = AF_INET;          // We are targeting IPv4
	hints.ai_protocol = IPPROTO_TCP;    // We are targeting TCP
	hints.ai_socktype = SOCK_STREAM;    // We are targeting TCP so its SOCK_STREAM

	if (!setup(uri))
	{
		std::cout << "Unable to setup" << std::endl;
	}

}

bool Client::setup(std::string uri)
{
	// Aquiring of the IPv4 address of a host using the newer
	// "getaddrinfo" function which outdated "gethostbyname".
	// It will search for IPv4 addresses using the TCP-Protocol.
	addrinfo* targetAdressInfo = NULL;
	DWORD getAddrRes = getaddrinfo(uri.c_str(), NULL, &(this->hints), &targetAdressInfo);
	if (getAddrRes != 0 || targetAdressInfo == NULL)
	{
		std::cout << "Could not resolve the Host Name" << std::endl;
		//WSACleanup();
		return -1;
	}

	// Create the Socket Address Informations, using IPv4
		// We dont have to take care of sin_zero, it is only used to extend the length of SOCKADDR_IN to the size of SOCKADDR
	SOCKADDR_IN sockAddr;
	sockAddr.sin_addr = ((struct sockaddr_in*) targetAdressInfo->ai_addr)->sin_addr;    // The IPv4 Address from the Address Resolution Result
	sockAddr.sin_family = AF_INET;  // IPv4
	sockAddr.sin_port = htons(80);  // HTTP Port: 80

	// We have to free the Address-Information from getaddrinfo again
	freeaddrinfo(targetAdressInfo);

	// Creation of a socket for the communication with the Web Server,
	// using IPv4 and the TCP-Protocol
	this->cnx = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->cnx == INVALID_SOCKET)
	{
		std::cout << "Creation of the Socket Failed" << std::endl;
		system("pause");
		//WSACleanup();
		return -1;
	}

	// Establishing a connection to the web Socket
	std::cout << "Connecting...\n";
	if (connect(cnx, (SOCKADDR*)&sockAddr, sizeof(sockAddr)) != 0)
	{
		std::cout << "Could not connect";
		system("pause");
		closesocket(cnx);
		//WSACleanup();
		return -1;
	}
	std::cout << "Connected.\n";
}

bool Client::sendbytes()
{
	// Sending a HTTP-GET-Request to the Web Server
	std::string httpRequest = "GET / HTTP/1.1\r\nHost: " + uri + "\r\nConnection: close\r\n\r\n";
	int sentBytes = send(cnx, httpRequest.c_str(), httpRequest.length(), 0);
	if (sentBytes < httpRequest.length() || sentBytes == SOCKET_ERROR)
	{
		std::cout << "Could not send the request to the Server" << std::endl;
		system("pause");
		closesocket(cnx);
		//WSACleanup();
		return -1;
	}

	// Receiving and Displaying an answer from the Web Server
	char buffer[10000];
	SecureZeroMemory(buffer, sizeof(buffer));
	int dataLen;
	while ((dataLen = recv(cnx, buffer, sizeof(buffer), 0) > 0))
	{
		int i = 0;
		while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {
			std::cout << buffer[i];
			i += 1;
		}
	}
}

bool Client::close()
{
	return false;
}

Client::~Client()
{
	closesocket(cnx);
}
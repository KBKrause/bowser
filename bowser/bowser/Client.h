#pragma once
#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <iostream>
#include <string>
#include "Payload.h"

class Client
{
	public:

		Client(std::string uri);

		// Executes a GET request.
		Payload* doGet();


		bool close();

		~Client();

	private:

		std::string uri;
		addrinfo hints;
		SOCKET cnx;

		bool setup(std::string uri);
};

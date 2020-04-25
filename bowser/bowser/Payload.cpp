#include "Payload.h"
#include <iostream>

using namespace std;

Payload::Payload()
{
	
}

Payload::Payload(string body)
{
	this->body = body;
}

void Payload::append(string more)
{
	this->body += more;
}

void Payload::print()
{
	cout << this->body << endl;
}

Payload::~Payload()
{
	
}
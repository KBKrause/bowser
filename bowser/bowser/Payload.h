#pragma once
#include <string>

using namespace std;

class Payload
{
public:

	Payload();
	Payload(string body);

	// Adds additional characters to the end of the body.
	void append(string more);

	// Prints the contents of body to stdout.
	void print();

	~Payload();

private:

	string body;

};


#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <vector>

class protocol
{
public:
	//Constructor
	protocol();

	//Destructor
	~protocol();


	//Decode the morse string into characters.
	ManagedString deCodeMorse(ManagedString);

	//Decode Binary into morse
	std::string  decodeBinMorse(std::string);

	char morseToAscii(ManagedString);
};
#endif

#include "protocol.h"
#include <string>

protocol::protocol()
{
}

protocol::~protocol()
{
}

//Decode the morse code string into ascii characters.
std::string protocol::deCodeMorse(std::string morse)
{
	std::string decoded;
	std::string substr;
	for (size_t i = 0; i < morse.size(); i++)
	{
		if ((morse[i] == '|') || (morse[i] == '/'))
		{
			decoded = decoded + '/';
			decoded = decoded + morseToAscii(substr);
			substr = "";
		}
		else if (morse[i] == ' ')
		{
			decoded = decoded + morseToAscii(substr);
			substr = "";
		}
		else
		{
			substr = substr + morse[i];
		}

	}

	return decoded;
}

std::string protocol::decodeBinMorse(std::string binary)
{
	std::string morse;

	int zeroCount = 0;
	int oneCount = 0;

	for (size_t i = 0; i < binary.length(); i++)
	{
		switch (binary[i])
		{
		case 0:
			oneCount = 0;
			zeroCount++;
			break;
		case 1:
			oneCount++;
			zeroCount = 0;

			if (oneCount >= 3)
			{
				morse.push_back('-');
				oneCount = 0;
			}
			else if ((oneCount == 1) && (binary[i+1] != 1))
			{
				morse.push_back('.');
			}


			break;
		}
		//Space between words.
		if ((zeroCount == 2) && (binary[i+2] != 0))
		{
			morse.push_back(' ');
		}
		else if ((zeroCount == 5) && (binary[i+1] != 0))
		{
			morse.push_back('/');
		}
		//End of message
		else if (zeroCount >= 10)
		{
			morse.push_back('|');
		}
	}

	return morse;
}

char protocol::morseToAscii(std::string morse)
{
	char ascii;

	if (morse == ".-")
		ascii = 'A';
	if(morse == "-...")
		ascii = 'B';
	if (morse == "-.-.")
		ascii = 'C';
	if (morse == "-..")
		ascii = 'D';
	if (morse == ".")
		ascii = 'E';
	if (morse == "..-.")
		ascii = 'F';
	if (morse == "--.")
		ascii = 'G';
	if (morse == "....")
		ascii = 'H';
	if (morse == "..")
		ascii = 'I';
	if (morse == ".---")
		ascii = 'J';
	if (morse == "-.-")
		ascii = 'K';
	if (morse == ".-..")
		ascii = 'L';
	if (morse == "--")
		ascii = 'M';
	if (morse == "-.")
		ascii = 'N';
	if (morse == "---")
		ascii = 'O';
	if (morse == ".--.")
		ascii = 'P';
	if (morse == "--.-")
		ascii = 'Q';
	if (morse == ".-.")
		ascii = 'R';
	if (morse == "-")
		ascii = 'T';
	if (morse == "..-")
		ascii = 'U';
	if (morse == "...-")
		ascii = 'V';
	if (morse == ".--")
		ascii = 'W';
	if (morse == "-..-")
		ascii = 'X';
	if (morse == "-.--")
		ascii = 'Y';
	if (morse == "--..")
		ascii = 'Z';

	return ascii;
}

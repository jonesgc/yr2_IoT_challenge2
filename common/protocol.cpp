#include "protocol.h"
#include <string>

//Constructor.
protocol::protocol()
{
  //Mapping binary values to characters.
  //Using international Morse code mapping.
	binToChar["01"] = 'A';
	binToChar["1000"] = 'B';
	binToChar["1010"] = 'C';
	binToChar["100"] = 'D';
	binToChar["0"] = 'E';
	binToChar["0010"] = 'F';
	binToChar["110"] = 'G';
	binToChar["0000"] = 'H';
	binToChar["00"] = 'I';
	binToChar["0111"] = 'J';
	binToChar["101"] = 'K';
	binToChar["0100"] = 'L';
	binToChar["11"] = 'M';
	binToChar["10"] = 'N';
	binToChar["111"] = 'O';
	binToChar["0110"] = 'P';
	binToChar["1101"] = 'Q';
	binToChar["101"] = 'R';
	binToChar["1"] = 'T';
	binToChar["001"] = 'U';
	binToChar["0001"] = 'V';
	binToChar["011"] = 'W';
	binToChar["1001"] = 'X';
	binToChar["1011"] = 'Y';
	binToChar["1100"] = 'Z';
}

//Destructor.
protocol::~protocol()
{
}

//Decode the morse code string into ascii characters.
std::string protocol::deCodeMorse(std::vector<std::string> morse)
{
	std::string decoded;

	//Iterate through vector each string is one morse character.
	for (size_t i = 0; i < morse.size(); i++)
	{
		decoded.push_back(binToChar[morse[i]]);
	}

	return decoded;
}

#include "protocol.h"
#include <string>

//Constructor.
protocol::protocol()
{
  //Mapping binary values to characters.
  //Using international Morse code mapping.
	binToChar[0b01] = 'A';
	binToChar[0b1000] = 'B';
	binToChar[0b1010] = 'C';
	binToChar[0b100] = 'D';
	binToChar[0b0] = 'E';
	binToChar[0b0010] = 'F';
	binToChar[0b110] = 'G';
	binToChar[0b0000] = 'H';
	binToChar[0b00] = 'I';
	binToChar[0b0111] = 'J';
	binToChar[0b101] = 'K';
	binToChar[0b0100] = 'L';
	binToChar[0b11] = 'M';
	binToChar[0b10] = 'N';
	binToChar[0b111] = 'O';
	binToChar[0b0110] = 'P';
	binToChar[0b1101] = 'Q';
	binToChar[0b101] = 'R';
	binToChar[0b1] = 'T';
	binToChar[0b001] = 'U';
	binToChar[0b0001] = 'V';
	binToChar[0b011] = 'W';
	binToChar[0b1001] = 'X';
	binToChar[0b1011] = 'Y';
	binToChar[0b1100] = 'Z';

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

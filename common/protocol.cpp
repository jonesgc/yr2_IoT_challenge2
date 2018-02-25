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

//This requires binary literal to be in morse compliance.
protocol::lookUp(int morse)
{
	char temp = binToChar[morse];
	return temp;
}

protocol::encryptAndDecrypt(int morse)
{
	int key [2] = {0b00100001, 0b00100010};
	int encrypted = morse;
	encrypted = encrypted ^ key [1];
	return encrypted;
}

protocol::encryptMsg(std::vector <int>msg)
{
	std::vector<int>encryptedMsg;

	for (size_t i = 0; i < msg.size(); i++)
	{
		encryptedMsg.push_back(encryptAndDecrypt(msg[i]));
	}
	return encryptedMsg;
}

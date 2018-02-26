#include "stdafx.h"
#include "protocol.h"


protocol::protocol()
{
	binToChar[0b01] = 'A';
	binToChar[0b1000] = 'B';
	binToChar[0b1010] = 'C';
	binToChar[0b100] = 'D';
}

protocol::~protocol()
{
}

int protocol::encryptAndDecrypt(int morse)
{
	int key[2] = { 0b00100001, 0b00100010 };
	int encrypted = morse;

	encrypted = encrypted ^ key[1];
	return encrypted;
}

char protocol::lookUp(int morse)
{
	char temp = binToChar[morse];
	return temp;
}

//Encrypts a binary message, these characters have already been pulled from digital.
std::vector<int> protocol::encryptMsg(std::vector<int>msg)
{
	std::vector<int>encryptedMsg;

	for (size_t i = 0; i < msg.size(); i++)
	{
		encryptedMsg.push_back(encryptAndDecrypt(msg[i]));
	}
	return encryptedMsg;
}


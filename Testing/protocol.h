#pragma once

#include<vector>
#include<map>

class protocol
{
public:
	protocol();
	~protocol();

	std::map<int, char>binToChar;

	int encryptAndDecrypt(int);

	char lookUp(int);

	std::vector<int>encryptMsg(std::vector<int>);

	
};
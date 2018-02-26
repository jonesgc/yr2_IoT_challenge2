#include "stdafx.h"
#include "decoder.h"

std::vector<char> decoder::decodeDigital(std::vector<int>dig)
{
	//Space counter 7 = end of message
	int zeroCount = 0;

	std::vector<char>decoded;

	//Strip noise and check for end of message.
	for (size_t i = 0; i < dig.size(); i++)
	{
		switch (dig[i])
		{
		case 0:
			//Check if the next part of the msg is 0 or 1.
			//This is to see if it was just a gap.
			switch (zeroCount)
			{

			//Gap between parts of same character.
			case 0:
				decoded.push_back('0');
				zeroCount++;
				break;

			//Gap between letters of same word.
			case 3:
				decoded.push_back(',');
				zeroCount++;
				break;

			//Space between words.
			case 5:
				decoded.push_back('/');
				zeroCount++;
				break;

			//End of message.
			case 10:
				decoded.push_back('|');
				zeroCount = 0;
				break;
			}
			break;
		case 1:
			//Check for three ones in a row.
			if ((dig[i+1]) && (dig[i+2]))
			{
				decoded.push_back('-');
				i= i+ 2;
				zeroCount = 0;
			}
			else
			{
				decoded.push_back('.');
				zeroCount = 0;
			}
			break;
		}
	}
	
	return decoded;
}

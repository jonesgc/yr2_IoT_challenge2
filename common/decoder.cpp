#include "decoder.h"

std::vector<char> decoder::decodeDigital(std::vector<int>dig)
{
	//Space counter 7 = end of message
	int zeroCount = 0;
	int oneCount = 0;
	std::vector<char>decoded;

	//Strip noise and check for end of message.
	for (size_t i = 0; i < dig.size(); i++)
	{
		switch (dig[i])
		{
		case 0:
			oneCount = 0;
			zeroCount++;
			break;
		case 1:
			oneCount++;
			zeroCount = 0;
			decoded.push_back('.');
			if (oneCount >= 3)
			{
				decoded.pop_back();
				decoded.pop_back();
				decoded.pop_back();
				decoded.push_back('-');
				oneCount = 0;
			}
			break;
		}
		//Space between words.
		if ((zeroCount >= 5) && (zeroCount <= 10))
		{
			decoded.push_back(',');
		}
		//End of message
		else if (zeroCount >= 10)
		{
			decoded.pop_back();
			decoded.push_back('|');
		}
	}
	return decoded;
}

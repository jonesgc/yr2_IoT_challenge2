
#include "protocol.h"
#include <string>

protocol::protocol()
{
}

protocol::~protocol()
{
}

//Decode the morse code string into ascii characters.
ManagedString protocol::deCodeMorse(ManagedString morse)
{
	ManagedString decoded;
	ManagedString substr;
	bool space = true;

	for (size_t i = 0; i < morse.length(); i++)
	{
		if ((morse.charAt(i) == '|') || (morse.charAt(i) == '/'))
		{
			decoded = decoded + ' ';
			decoded = decoded + morseToAscii(substr);

			if (morse.charAt(i) == '|')
			{
				decoded = decoded + '|';
			}
			else
			{
				decoded = decoded + '/';
			}
			substr = "";
		}
		else if (morse.charAt(i) == ' ')
		{
			if (space)
			{
				decoded = decoded + morseToAscii(substr);
				substr = "";
				space = false;
			}
			else
			{
				space = true;
				decoded = decoded + ' ';
				substr = "";
			}
		}
		else
		{
			substr = substr + morse.charAt(i);
		}

	}

	return decoded;
}

ManagedString protocol::encodeAscii(ManagedString ascii)
{
	ManagedString encoded = "";
	ManagedString substr;

	for (size_t i = 0; i < ascii.length(); i++)
	{
		if ((ascii.charAt(i) == '|'))
		{
			encoded = encoded + '|';
		}
		else if (ascii.charAt(i) == '/')
		{
			encoded = encoded + '/';
		}
		else if (ascii.charAt(i) == ' ')
		{
			encoded = encoded + ' ';
		}
		else
		{
			encoded = encoded + asciiToMorse(ascii.charAt(i));
			encoded = encoded + ' ';
		}

	}

	return encoded;
}

ManagedString protocol::encrypt(ManagedString ascii)
{

	ManagedString encrypted = "";
	int key = 2;

	for (size_t i = 0; i < ascii.length(); i++)
	{
		if ((ascii.charAt(i) == '|'))
		{
			encrypted = encrypted + '|';
		}
		else if (ascii.charAt(i) == '/')
		{
			encrypted = encrypted + '/';
		}
		else if(ascii.charAt(i) == ' ')
		{
			encrypted = encrypted + ' ';
		}
		else
		{
			encrypted = encrypted + char((ascii.charAt(i) + key));
		}

	}
	return encrypted;
}

ManagedString protocol::decrypt(ManagedString ascii)
{
	ManagedString decrypted = "";
	int key = -2;

	for (size_t i = 0; i < ascii.length(); i++)
	{
		if ((ascii.charAt(i) == '|'))
		{
			decrypted = decrypted + '|';
		}
		else if (ascii.charAt(i) == '/')
		{
			decrypted = decrypted + '/';
		}
		else if(ascii.charAt(i) == ' ')
		{
			decrypted = decrypted + ' ';
		}
		else
		{
			decrypted = decrypted + char((ascii.charAt(i) + key));
		}

	}
	return decrypted;
}

char protocol::morseToAscii(ManagedString morse)
{
	char ascii =0;

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
	if (morse == ".-.-.-")
		ascii = '.';
	if (morse == "--..--")
		ascii = ',';
	if (morse == "---...")
		ascii = ';';
	if (morse == "..--..")
		ascii = '?';
	if (morse == ".----.")
		ascii = '\'';
	if (morse == "-....-")
		ascii = '-';
	if (morse == "-..-.")
		//ascii = '/';
	if (morse == "-.--.-")
		ascii = '(';
	if (morse == ".-..-.")
		ascii = '"';
	if (morse == ".--.-.")
		ascii = '@';
	if (morse == "-...-")
		ascii = '=';

	return ascii;
}

ManagedString protocol::asciiToMorse(char ascii)
{

	if (ascii == 'A')
		return ".-";
	if (ascii == 'B')
		return "-...";
	if (ascii == 'C')
		return "-.-.";
	if (ascii == 'D')
		return "-..";
	if (ascii == 'E')
		return ".";
	if (ascii == 'F')
		return "..-.";
	if (ascii == 'G')
		return "--.";
	if (ascii == 'H')
		return "....";
	if (ascii == 'I')
		return "..";
	if (ascii == 'J')
		return ".---";
	if (ascii =='K')
		return  "-.-";
	if (ascii == 'L')
		return  ".-..";
	if (ascii == 'M')
		return "--";
	if (ascii == 'N')
		return "-.";
	if (ascii == 'O')
		return "---";
	if (ascii == 'P')
		return ".--.";
	if (ascii == 'Q')
		return "--.-";
	if (ascii == 'R')
		return ".-.";
	if (ascii == 'T')
		return "-";
	if (ascii == 'U')
		return "..-";
	if (ascii == 'V')
		return "...-";
	if (ascii == 'W')
		return ".--";
	if (ascii == 'X')
		return "-..-";
	if (ascii == 'Y')
		return "-.--";
	if (ascii == 'Z')
		return "--..";
	if (ascii == '.')
		return ".-.-.-";
	if (ascii == ',')
		return "--..--";
	if (ascii == ';')
		return "---...";
	if (ascii == '?')
		return "..--..";
	if (ascii == '\'')
		return ".----.";
	if (ascii == '-')
		return "-....-";
	if (ascii == '/')
		return "-..-.";
	if (ascii == '(' || ')')
		return  "-.--.-";
	if (ascii = '"')
		return  ".-..-.";
	if (ascii == '@')
		return  ".--.-.";
	if (ascii == '=')
		return  "-...-";

}

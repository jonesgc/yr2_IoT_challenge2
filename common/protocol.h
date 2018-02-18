#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <map>
#include <string>

class protocol
{
public:
  //Constructor
  protocol();

  //Destructor
  ~protocol();

  std::map <std::string, char> binToChar;

  //Decode the morse string into characters.
	std::string deCodeMorse(std::vector<std::string>);
};
#endif

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <map>
#include <string>
#include <vector>

class protocol
{
public:
  //Constructor
  protocol();

  //Destructor
  ~protocol();

  std::map <int, char> binToChar;

  //Find Ascii character for given binary literal.
  char lookUp(int);

  //Encrypt a binary literal via XOR.
  int encryptAndDecrypt(int);

  //Encrypt/Decrypt a message.
  std::vector<int>encryptMsg(std::vector<int>);
};
#endif

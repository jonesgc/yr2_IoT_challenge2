  //Author: Gregory Jones
  //This is the main file for Challenge 2 submission.
  //See readme.md for more infomation
  //Project Start Date: 17/02/2018

  //START OF CODE
  #include "MicroBit.h"
  #include <string>
  #include "../common/protocol.h"

  MicroBit uBit;
  MicroBitSerial serial(USBTX, USBRX);
  //TODO 1. IMPLEMENT DECODING methods below.
  //     2. Output decoded string on microbit.
  /*
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
*/



MicroBitPin P2(MICROBIT_ID_IO_P2, MICROBIT_PIN_P2, PIN_CAPABILITY_DIGITAL);
  int main()
  {
    // Initialise the micro:bit runtime.
    uBit.init();

    //Character counter used to aquire the morse character from the digital signal.
    //Every "tick" of this receiver the pins are read and either of these counters are incremented.
    int digLo =0;
    int digHi =0;

    //Decoded morse message, needs to be decoded again into ascii.
    std::string deMsg;

    //uint64_t reading = system_timer_current_time();
    while(1)
    {
      if(P2.getDigitalValue() == 1)
      {
        //If 3 dots in a row with no space then its a dash.
        if(digHi >= 3)
        {
          uBit.display.print("-");
          digHi = 0;
        }
        else
        {
          //Add a dot to the string
          uBit.display.print(".");
          digHi++;
        }

      }

      if(digLo >= 7)
      {
        uBit.display.print("End of message");
      }
      else
      {
        //Add a space
        uBit.display.print("s");
        digLo++;
      }

      //uint64_t delta = system_timer_current_time() - reading;

      //serial.baud(115200);
      //serial.send(int(delta));

      //Time Unit is 500 milliseconds.
      uBit.sleep(500);
    }

  }
  //END OF FUNCTIONS
  //END OF CODE

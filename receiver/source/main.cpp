  //Author: Gregory Jones
  //This is the main file for Challenge 2 submission.
  //See readme.md for more infomation
  //Project Start Date: 17/02/2018

  //START OF CODE
  #include "MicroBit.h"
  #include <vector>
  #include "../common/protocol.h"

  MicroBit uBit;
  MicroBitSerial serial(USBTX, USBRX);


MicroBitPin P2(MICROBIT_ID_IO_P2, MICROBIT_PIN_P2, PIN_CAPABILITY_DIGITAL);
  int main()
  {
    // Initialise the micro:bit runtime.
    uBit.init();

    //Character counter used to aquire the morse character from the digital signal.
    //Every "tick" of this receiver the pins are read and either of these counters are incremented.
    int digLo =0;
    int digHi =0;
    bool msg = false;

    //Decoded morse message, needs to be decoded again into ascii.
    std::vector<char> deMsg;

    //Binary String from pin.
    std::vector<int> binStr;
    while(1)
    {


    while(msg == true)
    {
      serial.baud(115200);
      if(P2.getDigitalValue() == 1)
      {
        //If 3 dots in a row with no space then its a dash.
        if(digHi > 2)
        {
          uBit.display.print("-");
          binStr.push_back(1);
          serial.send('1');
          uBit.sleep(500);
          digHi = 0;
          digLo = 0;
        }
        else
        {
          //Add a dot to the string
          uBit.display.print(".");
          binStr.push_back(1);
          serial.send('1');
          uBit.sleep(500);
          digHi++;
          digLo = 0;
        }
      }

      if(P2.getDigitalValue() == 0)
      {
        if(digLo >= 7)
        {
          uBit.display.print("C");
          uBit.sleep(500);
          msg = false;
          break;
        }
        uBit.display.print("0");
        binStr.push_back(1);
        serial.send('0');
        uBit.sleep(500);
        digLo++;
      }

      //Time Unit is 500 milliseconds.
      uBit.display.clear();
    }

    //Waiting for a signal.
    while(msg == false)
    {
      uBit.display.print("W");
      if(P2.getDigitalValue() == 1)
      {
        msg = true;
        break;
      }
    }

  }
  }
  //END OF FUNCTIONS
  //END OF CODE

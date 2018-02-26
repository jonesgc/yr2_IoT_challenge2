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

    int baseRead = 0;
    int delta = 0;
    //Decoded morse message, needs to be decoded again into ascii.
    std::vector<char> deMsg;

    //Binary String from pin.
    std::vector<int> binStr;

    while(1)
    {
    while(msg == true)
    {
      // read current number of milliseconds
      baseRead = system_timer_current_time();

      if(P2.getDigitalValue() == 1)
      {
        //Measure how long pin was either on or off for.
        while(P2.getDigitalValue() == 1)
        {
          uBit.display.print("1");
        }

        delta = system_timer_current_time() - baseRead;
        if(delta > 1000)
        {
          uBit.display.print("-");
          uBit.sleep(500);
        }
        else if (delta > 500)
        {
          uBit.display.print(".");
          uBit.sleep(500);
        }
        digLo=0;
        uBit.display.clear();
      }


      if(P2.getDigitalValue() == 0)
      {
        while(P2.getDigitalValue() == 0)
        {
          uBit.display.print("0");
          digLo++;
          uBit.sleep(500);
          break;
        }

        //End of message.
        if(digLo >= 15)
        {
          uBit.display.print("E");
          uBit.sleep(500);
          msg = false;
          break;
        }
        uBit.display.clear();
      }

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

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




  //FUNCTION PROTOTYPES

  //END OF FUNCTION PROTOTYPES

MicroBitPin P2(MICROBIT_ID_IO_P2, MICROBIT_PIN_P2, PIN_CAPABILITY_DIGITAL);
  int main()
  {
    // Initialise the micro:bit runtime.
    uBit.init();

    //Character counter used to aquire the morse character from the digital signal.
    //Every "tick" of this receiver the pins are read and either of these counters are incremented.
    int digLo =0;
    int digHi =0;
    bool space = false;
    //Decoded morse message, needs to be decoded again into ascii.
    std::string deMsg;

    //uint64_t reading = system_timer_current_time();
    while(1)
    {
      if(P2.getDigitalValue() == 1)
      {
        uBit.display.print("1");
        digHi++;

        if(digHi == 3)
        {
          uBit.display.print("A");
          digHi = 0;
        }
      }

      if(P2.getDigitalValue() == 0)
      {
        uBit.display.print("0");
        digLo++;
        //Add a space
        if((digLo == 1) && (space == false))
        {
          uBit.display.print("-");
          space = true;
          digLo = 0;
        }
        if(digLo >= 2)
        {
          uBit.display.print("B");
          digLo = 0;
          space = false;
        }
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

  //Author: Gregory Jones
  //This is the main file for Challenge 2 submission.
  //See readme.md for more infomation
  //Project Start Date: 17/02/2018

  //START OF CODE
  #include "MicroBit.h"

  MicroBit uBit;
  MicroBitSerial serial(USBTX, USBRX);




  //FUNCTION PROTOTYPES

  //END OF FUNCTION PROTOTYPES

MicroBitPin P2(MICROBIT_ID_IO_P2, MICROBIT_PIN_P2, PIN_CAPABILITY_DIGITAL);
  int main()
  {
    // Initialise the micro:bit runtime.
    uBit.init();

    while(1)
    {
      if(P2.getDigitalValue() == 1)
      {
        uBit.display.print("1");
        uBit.sleep(1000);
      }

      if(P2.getDigitalValue() == 0)
      {
        uBit.display.print("0");
        uBit.sleep(1000);
      }
      uBit.display.clear();
    }

  }
  //END OF FUNCTIONS
  //END OF CODE

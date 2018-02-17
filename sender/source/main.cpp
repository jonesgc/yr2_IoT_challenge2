  //Author: Gregory Jones
  //This is the main file for Challenge 2 submission.
  //See readme.md for more infomation
  //Project Start Date: 29/01/2018

  //START OF CODE
  #include "MicroBit.h"

  MicroBit uBit;
  MicroBitSerial serial(USBTX, USBRX);



  //FUNCTION PROTOTYPES

  //END OF FUNCTION PROTOTYPES

MicroBitButton buttonA(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A);

MicroBitPin P1(MICROBIT_ID_IO_P1, MICROBIT_PIN_P1, PIN_CAPABILITY_DIGITAL);
  int main()
  {
    // Initialise the micro:bit runtime.
    uBit.init();

    bool pressed = false;

   while(1)
   {
       // read current number of milliseconds
       uint64_t baseReading = system_timer_current_time();

       // loop while button A pressed
       while (buttonA.isPressed())
       {
           pressed = true;
       }

       // time of loop execution
       uint64_t delta = system_timer_current_time() - baseReading;

       // if button was pressed
       if (pressed)
       {
           // geater than a second
           if (delta > 1000)
           { // > 1 sec
               uBit.display.print("1");
               P1.setDigitalValue(1);
               uBit.sleep(500);
           }
           // greater than 1/2 sec, but less than sec
           else if (delta > 500)
           {
               uBit.display.print("0");
               P1.setDigitalValue(0);
               uBit.sleep(500);
           }

           pressed = false;
           uBit.display.clear();
       }
   }



    //END OF PRE-GAME INITALISATION

    //SERIAL DEBUG
    //serial debugging statements
    //serial.baud(115200);
    //serial.send("The temperature is:");
    //serial.send(temp);
    //serial.send(" The Charge rate is:");
    //serial.send(cRate);
    //END OF SERIAL DEBUG

    release_fiber();
  }

  //FUNCTIONS

  //END OF FUNCTIONS
  //END OF CODE

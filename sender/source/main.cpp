  //Author: Gregory Jones
  //This is the main file for Challenge 2 submission.
  //See readme.md for more infomation
  //Project Start Date: 17/02/2018

  //START OF CODE
  #include "MicroBit.h"

  MicroBit uBit;
  MicroBitSerial serial(USBTX, USBRX);

  bool msg;

  //FUNCTION PROTOTYPES
  void messageStart(MicroBitEvent e);
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
          uint64_t reading = system_timer_current_time();

          // loop while button A pressed
          while (buttonA.isPressed())
          {
              pressed = true;
          }

          // time of loop execution
          uint64_t delta = system_timer_current_time() - reading;

          //if button was pressed
          if (pressed)
          {
              //Geater than a second = dash (hold on for three tu).
              if (delta > 1000)
              {
                  uBit.display.print("-");
                  P1.setDigitalValue(1);
                  uBit.sleep(1500);
              }
              //A dot, a single 1 for a single tu.
              else
              {
                uBit.display.print(".");
                P1.setDigitalValue(1);
                uBit.sleep(500);
              }

              pressed = false;
              uBit.display.clear();
          }

          P1.setDigitalValue(0);
          uBit.sleep(500);
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

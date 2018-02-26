//Author: Gregory Jones
//This is the main file for Challenge 2 submission.
//See readme.md for more infomation
//Project Start Date: 17/02/2018

//START OF CODE
#include "MicroBit.h"
#include <vector>
#include "../common/decoder.h"
#include "../common/decoder.cpp"

MicroBit uBit;
MicroBitSerial serial(USBTX, USBRX);

//FUNCTION PROTOTYPES
//END OF FUNCTION PROTOTYPES

MicroBitButton buttonA(MICROBIT_PIN_BUTTON_A, MICROBIT_ID_BUTTON_A);
MicroBitButton buttonB(MICROBIT_PIN_BUTTON_B, MICROBIT_ID_BUTTON_B);

MicroBitPin P1(MICROBIT_ID_IO_P1, MICROBIT_PIN_P1, PIN_CAPABILITY_DIGITAL);
MicroBitPin P2(MICROBIT_ID_IO_P2, MICROBIT_PIN_P2, PIN_CAPABILITY_DIGITAL);

int main()
{
  // Initialise the micro:bit runtime.
  uBit.init();

  bool sender = false;

  //Message storage vectors.
  std::vector<char> decoded;
  std::vector<char> ascii;

  decoder decoder;
  //Wrapper that allows user to switch between send/recieve
  while(1)
  {
    //Sender. The microbit that the button was pressed on switches into this state.
    //The receiver microbit gets a handshake that tells it to move into receiver state.
    if (buttonB.isPressed())
    {
      uBit.display.print('S');
      sender = true;
      //Send Handshake to change other microbit into receiver state.
      P1.setDigitalValue(1);
      uBit.sleep(2000);
      P1.setDigitalValue(0);
      uBit.display.clear();
      bool input = true;
      bool aPress = false;

      //Timing Variables.
      uint64_t baseRead = 0;
      uint64_t delta = 0;

      serial.baud(115200);
        while(sender)
        {
          // read current number of milliseconds
          baseRead = system_timer_current_time();

            // loop while button A pressed
            while (buttonA.isPressed())
            {
                aPress = true;
            }

            // time of loop execution
          delta = system_timer_current_time() - baseRead;

            //if button was pressed
            if (aPress)
            {
                //Geater than a second = dash (hold on for three tu).
                if ((delta > 750) && (input))
                {
                    uBit.display.print("-");
                    P1.setDigitalValue(1);
                    input = false;
                    uBit.sleep(1500);
                }
                //A dot, a single 1 for a single tu.
                else if(input)
                {
                  uBit.display.print(".");
                  P1.setDigitalValue(1);
                  input = false;
                  uBit.sleep(500);
                }

                aPress = false;
                input = true;
                uBit.display.print("0");
                P1.setDigitalValue(0);
            }

            //Stop sending and return to wrapper.
            if(buttonB.isPressed())
            {
              uBit.display.print('E');
              sender = false;
              uBit.sleep(1000);
              uBit.display.clear();
              break;
            }
        }
    }

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
    bool test=false;
    uBit.display.print("W");
    //Listen to P2 for signal
    if(P2.getDigitalValue()==1)
    {
      test = true;
      uBit.display.print("L");
      uBit.sleep(500);
    }

    if(test)
    {
      msg = true;
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
            test = false;
            break;
          }
          uBit.display.clear();
        }

      }
  }
}
  release_fiber();
}

//FUNCTIONS
//END OF FUNCTIONS
//END OF CODE

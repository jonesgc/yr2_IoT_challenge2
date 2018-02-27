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
  uBit.display.scroll("init");
  serial.baud(115200);
  serial.send("\r\n mbit starting \r\n");

  ManagedString packet;

  decoder decoder;
  //Wrapper that allows user to switch between send/recieve
  while(1)
  {
    bool sender = false;



    //Message storage vectors.
    std::vector<char> decoded;
    std::vector<char> ascii;

    //Sender. The microbit that the button was pressed on switches into this state.
    //The receiver microbit gets a handshake that tells it to move into receiver state.
    if (buttonB.isPressed())
    {
      uBit.display.print('S');
      sender = true;
      //Send Handshake to change other microbit into receiver state.

      uBit.display.clear();
      bool input = true;
      bool aPress = false;
      bool bPress = false;

      //Timing Variables.
      uint64_t baseRead = 0;
      uint64_t delta = 0;
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
                    packet = packet + "-";
                    input = false;
                    uBit.sleep(1500);
                }
                //A dot, a single 1 for a single tu.
                else if(input)
                {
                  uBit.display.print(".");
                  packet = packet + ".";
                  input = false;
                  uBit.sleep(500);
                }

                aPress = false;
                input = true;
                packet = packet + " ";
                uBit.display.clear();
                uBit.sleep(500);
            }

            // loop while button A pressed
            while (buttonB.isPressed())
            {
                bPress = true;
            }

            delta = system_timer_current_time() - baseRead;

            if(bPress)
            {
              //End the message.
              if ((delta > 1000) && (input))
              {
                  uBit.display.print("|");
                  packet = packet + "|";
                  input = false;
                  sender=false;
                  serial.send("sending packet: ");
                  serial.send(packet);
                  serial.send("\r\n");
                  P1.setDigitalValue(1);
                  uBit.sleep(50);
                  P1.setDigitalValue(0);
                  for (size_t i = 0; i < packet.length(); i++)
                  {

                    char temp = packet.charAt(i);
                    serial.send("sending: ");
                    serial.send(temp);
                    serial.send("\r\n");
                    switch(temp)
                    {
                      case '.':
                        P1.setDigitalValue(1);
                        uBit.sleep(500);
                        break;
                      case '-':
                        P1.setDigitalValue(1);
                        uBit.sleep(1500);
                        break;
                      case '/':
                        P1.setDigitalValue(0);
                        uBit.sleep(1500);
                        break;
                      case '|':
                        P1.setDigitalValue(0);
                        uBit.sleep(2000);
                        break;
                    }
                  }
                  break;
              }
              //A dot, a single 1 for a single tu.
              else if((input) && (delta < 1000))
              {
                uBit.display.print("/");
                packet = packet + "/";
                input = false;
                uBit.sleep(500);
              }

              bPress = false;
              input = true;
              uBit.display.clear();
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

    //Binary String from pin.
    std::vector<int> binStr;
    bool test=false;
    uBit.display.print("W");
    //Listen to P2 for signal
    if(P2.getDigitalValue()==1)
    {
      test = true;
      msg = true;
      uBit.display.print("L");
      uBit.sleep(500);
      uBit.display.clear();
    }

    if(test)
    {
      while(msg == true)
      {
        serial.send("entering recieve loop\r\n");
        // read current number of milliseconds


        if(P2.getDigitalValue() == 1)
        {
          baseRead = system_timer_current_time();
          while(P2.getDigitalValue() == 1)
          {

          }

          delta = system_timer_current_time() - baseRead;

          //Geater than a second = dash (hold on for three tu).
          if (delta > 1500)
          {
            serial.send("- recived \r\n");
              uBit.display.print("-");
              packet = packet + "-";
              serial.send('-');
          }
          //A dot, a single 1 for a single tu.
          else if((delta > 400) && (delta < 700))
          {
            serial.send(". recived \r\n");
            uBit.display.print(".");
            packet = packet + ".";
            serial.send('.');
          }
        }

        if(P2.getDigitalValue()==0)
        {
          baseRead = system_timer_current_time();
          serial.send("pin off detected 232\r\n");
          while(P2.getDigitalValue() == 0)
          {

          }

          delta = system_timer_current_time() - baseRead;
          serial.send(delta);
          if(delta <=1000)
          {
            serial.send("delta too low, cba\r\n");

          }

          if ((delta > 1500) && (delta < 2000))
          {
            serial.send("/ appended 245 \r\n");
              uBit.display.print("/");
              packet = packet + "/";
              serial.send('/');
          }
          //A dot, a single 1 for a single tu.
          else if((delta >= 2500) && (delta < 3100))
          {
            serial.send("eof recived");
            serial.send("\r\n");
            uBit.display.print("|");
            packet = packet + "|";
            serial.send('|');
            packet = 0;
            msg = false;
            test = false;

          }
          else{
            serial.send("delta too high, missing\r\n");

          }
            serial.send("end of recive loop\r\n");
        }
        serial.send("exiting recive loop\r\n");

        uBit.sleep(500);
        uBit.display.clear();
      }
  }
}
  release_fiber();
}

//FUNCTIONS
//END OF FUNCTIONS
//END OF CODE

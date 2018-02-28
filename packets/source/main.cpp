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

    //Timing Variables.
    uint64_t baseRead = 0;
    uint64_t delta = 0;


    //Message storage vectors.
    std::vector<char> decoded;
    std::vector<char> ascii;

    //Sender. The microbit that the buttonA was pressed on switches into this state.
    //Messages are sent from P1 to P2.
    if (buttonB.isPressed())
    {
      uBit.display.print('S');
      sender = true;
      uBit.display.clear();
      bool input = true;
      bool aPress = false;
      bool bPress = false;

        while(sender == true)
        {
          baseRead = system_timer_current_time();

            //Measure how long buttonA is pressed for.
            while (buttonA.isPressed())
            {
                aPress = true;
            }

            delta = system_timer_current_time() - baseRead;

            //If buttonA was pressed, morse character depends on length of press.
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

                //Space between morse characters.
                aPress = false;
                input = true;
                packet = packet + " ";
                uBit.display.clear();
                uBit.sleep(500);
            }

            //Measure how long buttonB is pressed for.
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

                  //Set receiver microbit into listening state.
                  P1.setDigitalValue(1);
                  uBit.sleep(50);
                  P1.setDigitalValue(0);

                  //Send Packet contents.
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
                      case ' ':
                        P1.setDigitalValue(0);
                        uBit.sleep(500);
                        break;
                      case '/':
                        P1.setDigitalValue(0);
                        uBit.sleep(1500);
                        break;
                      case '|':
                        P1.setDigitalValue(0);
                        uBit.sleep(3000);
                        break;
                    }
                  }
                  //End of message sent, break out of sender state.
                  break;
              }
              //Space separating words.
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
    bool pin = false;

    //Binary String from pin.
    ManagedString binStr;
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
      P2.setDigitalValue(0);
    }

    if(test)
    {
      while(msg == true)
      {
        if(P2.getDigitalValue() == 1)
        {
          baseRead = system_timer_current_time();

          while(P2.getDigitalValue() == 1)
          {
            pin = true;
          }
          serial.send("reading 1 \r\n");
          delta = system_timer_current_time() - baseRead;
          serial.send(int(delta));
          //Geater than a second = dash (hold on for three tu).
          if ((delta > 1400) && (delta < 1700))
          {
            serial.send("- recived \r\n");
              uBit.display.print("-");
              packet = packet + "-";
          }
          //A dot, a single 1 for a single tu.
          else if((delta > 400) && (delta < 1200))
          {
            serial.send(". recived \r\n");
            uBit.display.print(".");
            packet = packet + ".";
          }
          else{
            serial.send("delta too high. \r\n");
          }
        }

        if(P2.getDigitalValue()==0)
        {
          baseRead = system_timer_current_time();

          serial.send("pin off detected 232\r\n");
          while(P2.getDigitalValue() == 0)
          {
            pin = true;
            digLo++;
            if(digLo > 1000000)
            {
              serial.send("END OF MESSAGE");
              break;
            }
          }
          serial.send("reading 0 \r\n");
          delta = system_timer_current_time() - baseRead;
          serial.send(int(delta));

          if((delta < 1000) && (delta > 400))
          {
            serial.send("space appended 249 \r\n");
            uBit.display.print(" ");
            packet = packet + " ";
            serial.send(' ');
          }
          else if ((delta > 1050) && (delta < 2000))
          {
            serial.send("/ appended 256 \r\n");
              uBit.display.print("/");
              packet = packet + "/";
              serial.send('/');
          }
          //End of message detected.
          else if(delta >= 2500)
          {
            serial.send("eof recived");
            serial.send("\r\n");
            uBit.display.print("|");
            packet = packet + "|";
            serial.send('|');
            for (size_t i = 0; i < packet.length(); i++)
            {
              uBit.display.print(packet.charAt(i));
              uBit.sleep(500);
            }
            packet = 0;
            msg = false;
            test = false;
            P2.setDigitalValue(0);
            break;
          }
          else
          {
            serial.send("delta too high, missing\r\n");
          }
        }
        serial.send("exiting recive loop\r\n");
        pin = false;
        uBit.display.clear();
        }
      }
  }
  release_fiber();
}

//FUNCTIONS
//END OF FUNCTIONS
//END OF CODE

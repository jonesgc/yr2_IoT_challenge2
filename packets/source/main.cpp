//Authors: Gregory Jones, Sean Kearney
//This is the main file for Challenge 2 submission.
//See readme.md for more infomation
//Project Start Date: 17/02/2018

//START OF CODE
#include "MicroBit.h"
#include <vector>
#include "../common/protocol.h"
#include "../common/protocol.cpp"

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
//begin test
  ManagedString testyboi66576("foo");
  serial.send("sending: ");
  serial.send(testyboi66576);
  serial.send("\r\n");
  testyboi66576 = "";
  serial.send("1sending: ");
  serial.send(testyboi66576);
  serial.send("\r\n");
  testyboi66576 = "bar";
  serial.send("2sending: ");
  serial.send(testyboi66576);
  serial.send("\r\n");


  protocol protocol;

  ManagedString packet;
  ManagedString decoded;
  ManagedString ascii;
  //Wrapper that allows user to switch between send/recieve
  while(1)
  {
    bool sender = false;

    //Timing Variables.
    uint64_t baseRead = 0;
    uint64_t delta = 0;




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

                uBit.display.clear();
                aPress = false;
                input = true;
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
              if ((delta > 2000) && (input))
              {
                  //Append end of message character.
                  uBit.display.print("|");
                  packet = packet + "|";
                  input = false;
                  sender=false;
                  serial.send("sending packet: ");
                  serial.send(packet);
                  serial.send("\r\n");

                  //Decode packet.
                  decoded = protocol.deCodeMorse(packet);
                  serial.send("decoded packet: ");
                  serial.send(decoded);
                  serial.send("\r\n");

                  //Encrypt decoded packet.
                  ascii = protocol.encrypt(decoded);
                  serial.send("encrypted packet: ");
                  serial.send(ascii);
                  serial.send("\r\n");

                  //Re-encode to morse;
                  packet = protocol.encodeAscii(ascii);
                  serial.send("re-encoded packet: ");
                  serial.send(packet);
                  serial.send("\r\n");

                  //Set receiver microbit into listening state.
                  P1.setDigitalValue(1);
                  uBit.sleep(500);
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
                        P1.setDigitalValue(0);
                        uBit.sleep(5);
                        break;
                      case '-':
                        P1.setDigitalValue(1);
                        uBit.sleep(1500);
                        P1.setDigitalValue(0);
                        uBit.sleep(5);
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
                  decoded = "";
                  packet = "";
                  break;
              }
              //Space separating words.
              else if((input) && (delta >= 1000) && (delta <= 2000))
              {
                uBit.display.print("/");
                packet = packet + "/";
                input = false;
                uBit.sleep(500);
              }
              else if((input) && (delta < 1000) && (delta >= 400))
              {
                uBit.display.print("S");
                packet = packet + " ";
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

    bool test=false;
    uBit.display.print("W");
    //Listen to P2 for signal
    if(P2.getDigitalValue()==1)
    {
      test = true;
      msg = true;
      P2.setDigitalValue(0);
      uBit.display.print("L");
      uBit.sleep(500);
      uBit.display.clear();
    }

    //Receiver State.
    if(test)
    {
      while(msg == true)
      {
        //Read pin high.
        //Possible outcomes are: . or -
        if(P2.getDigitalValue() == 1)
        {
          //Measure time.
          baseRead = system_timer_current_time();

          while(P2.getDigitalValue() == 1)
          {
            digHi++;
            pin = true;
            //Failsafe breakout.
            if(digHi > 1000000)
            {
              serial.send("END OF MESSAGE");
              msg = false;
              test = false;
              break;
            }
          }
          serial.send("reading 1 \r\n");
          //Get duration.
          delta = system_timer_current_time() - baseRead;
          serial.send(int(delta));

          //Get morse from digital signals.
          //Geater than a second = dash (hold on for three tu).
          if ((delta > 1400) && (delta < 3000))
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

        //Read pin low.
        //Possible outcomes: space, / or |.
        if(P2.getDigitalValue()==0)
        {
          //Measure time.
          baseRead = system_timer_current_time();

          serial.send("pin off detected 232\r\n");
          while(P2.getDigitalValue() == 0)
          {
            pin = true;
            digLo++;
            if(digLo > 1000000)
            {
              serial.send("END OF MESSAGE");
              msg = false;
              test = false;
              break;
            }
          }
          serial.send("reading 0 \r\n");
          //Determine duration.
          delta = system_timer_current_time() - baseRead;
          serial.send(int(delta));

          //Space between letters.
          if((delta < 1000) && (delta > 400))
          {
            serial.send("space appended 249 \r\n");
            uBit.display.print(" ");
            packet = packet + " ";
            serial.send(' ');
          }
          //Space between words.
          else if ((delta > 1000) && (delta < 2500))
          {
            serial.send("/ appended 256 \r\n");
              uBit.display.print("/");
              packet = packet + "/";
              serial.send('/');
          }
          //End of message detected.
          else if(delta >= 2700)
          {
            serial.send("eof recived");
            serial.send("\r\n");
            uBit.display.print("|");
            packet = packet + "|";
            serial.send('|');
            serial.send("Packet is: ");
            serial.send(packet);
            serial.send("\n");

            //This is the encrypted packet.
            decoded = protocol.deCodeMorse(packet);
            serial.send("Decoded is: ");
            serial.send(decoded);
            serial.send("\n");

            //Decrypt the packet.
            ascii = protocol.decrypt(decoded);
            serial.send("Decrypted + decoded is: ");
            serial.send(ascii);
            serial.send("\n");

            //Display packet contents.
            uBit.display.scroll(ascii);
            packet = "";
            decoded = "";
            ascii= "";
            //Return to waiting state.
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

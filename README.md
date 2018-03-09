IOT_Challenge2
Authors: Gregory Jones + Sean Kearney

Location of oo resources:
IOT_Challenge2/common/protocol.h
IOT_Challenge2/common/protocol.cpp

Build instructions:
1. Clone IOT_Challenge2 repo
2. Cd into IOT_Challenge2/packets
3. execute yt build
4. cd into build/bbc-microbit-classic-gcc/source
5. Copy the packets-combined.hex file into two microbits.

Program Instructions:
1. Connect the two microbits with crocodile clip calbes.
2. One cable must be attached on the ground connector of both microbits.
3. Another cable should be connected to PIN 1 of the microbit you wish to send from.
4. The Reiceiver microbit should be connected via PIN 2.

To start message sending between the two connected microbits. On the device you whish to send from press buttonB. This will move this microbit into the sending state.
The microbit will now buffer your input into a "packet" so there is no rush in sending. Each button has a different function which are outlined below.

ButtonA:
    Short press: morse code dot .
    Long press: morse code dash -
    
ButtonB:
    Short press: space between characters of the same word.
    Medium press: morse code space between words /
    Long press: End of message morse code |
        This will terminate the message sending sequence and marks the end of the packet.
        
Once your message is finished the microbit will beign sending to the connected microbit. You will know if this is working because the microbit will stop displaying W and show L.
The receiver will decrypt and decode the sent message and display it once across the LED display.
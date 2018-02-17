#ifndef PROTOCOL_H
#define PROTOCOL_H

while(1)
{
    // read current number of milliseconds
    uint64_t baseReading = system_timer_current_time();

    // loop while button A pressed
    //while (buttonA.isPressed())
    //{
        //pressed = true;
    //}

    // time of loop execution
    uint64_t delta = system_timer_current_time() - baseReading;

    // if button was pressed
    if (pressed)
    {
        // geater than a second
        if (delta > 1000)
        { // > 1 sec
            uBit.display.print("1");
            uBit.sleep(500);
        }
        // greater than 1/2 sec, but less than sec
        else if (delta > 500)
        {
            uBit.display.print("0");
            uBit.sleep(500);
        }

        pressed = false;
        uBit.display.clear();
    }
}
#endif

  //Author: Gregory Jones
  //This is the main file for Challenge 1 submission.
  //See readme.md for more infomation
  //Project Start Date: 29/01/2018

  //START OF CODE
  #include "MicroBit.h"

  MicroBit uBit;
  MicroBitSerial serial(USBTX, USBRX);


  //Player Variables
  //The Player cannot move up, no Y axis needed.
  //GLOBAL VARIABLES
  static int playerX;

  //Charge level of the bLaser
  double charge= -100;
  //END OF GLOBAL VARIABLES

  //FUNCTION PROTOTYPES
  void shoot(MicroBitEvent e);
  void bLaser(MicroBitEvent e);
  int findBrightness(double s);
  void displayPlayer(int x, int y, int c);
  void playerMove(MicroBitEvent e);
  void displayEnemies(int n);
  void moveEnemies(int t);
  int chargeRate(int temperature);
  //END OF FUNCTION PROTOTYPES

  int main()
  {
    // Initialise the micro:bit runtime.
    uBit.init();

    //VARIABLES
    //Lose condition variable used to control the game loop.
    //If an enemy reaches the bottom row this set 0, ending the game.
    int hp = 1;

    //Score is the highest wave the player reached, this could be modified
    //along with the timing of enemy movement to increase difficulty.
    int score = 0;
    //Wave counter;
    int wave = 1;

    //Each game tick is spaced by a minimum of 10ms delay.
    int tick=1;

    //Value used in movement of the enemies, this can be manipulated
    //to change far the enemies move per tick.
    int offset=0;

    //Read the temperature on the surface of the nrf51822.
    //The temperature read is in degrees C.
    int temp = uBit.thermometer.getTemperature();
    int cRate = chargeRate(temp);
    //END OF VARIABLES

    //PRE-GAME INITALISATION
    //Listenen for button A to be pressed, fires the "single" shot weapon.
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, shoot);

    //Listen for Button B to be held, fires the "charge laser".
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, bLaser);

    //Event listener for accelerometer.
    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_EVT_ANY, playerMove);

    //Sets the display to grayscale, enables a range of brightnesses for the LEDS.
    uBit.display.setDisplayMode(DISPLAY_MODE_GREYSCALE);

    //Display inital enemies to start the game.
    displayEnemies(5);
    //END OF PRE-GAME INITALISATION

    //SERIAL DEBUG
    //serial debugging statements
    //serial.baud(115200);
    //serial.send("The temperature is:");
    //serial.send(temp);
    //serial.send(" The Charge rate is:");
    //serial.send(cRate);
    //END OF SERIAL DEBUG

    //Main game loop.
    while (hp != 0)
    {

      //Charge the bLaser. Rate determined before main game loop.
      if(charge >= 10000)
      {
        charge = 10000;
      }
      else
      {
        charge = charge + cRate;
      }

      //Light up the "player" LED with given co-ords.
      displayPlayer(playerX,4,findBrightness(charge));

      //Check row 5 for an enemy, only enemies have brightness 255 on row 5.
      for (size_t i = 0; i <= 4; i++)
      {
        if(uBit.display.image.getPixelValue(i,4) == 255)
        {
          hp = 0;
        }
      }

      //Tick complete, move all enemies down one row.
      if(tick >= 1000)
      {
        //Move the enemies.
        moveEnemies(offset);
        tick = 0;
        offset++;
      }

      //Spawn a new wave.
      if(offset == 3)
      {
        wave++;
        displayEnemies(wave);
        offset = 0;
      }

      //The players score is the wave that they reached.
      score = wave;

      tick++;
      uBit.sleep(10);
    }

    //Display score + game over message.
    uBit.display.scroll("GAME OVER");
    uBit.display.scroll("SCORE = ");
    uBit.display.scroll(score);

    release_fiber();
  }

  //FUNCTIONS

  //Shoot command.
  //Button A is the left button, on single press fire a single projectile.
  //On detection of a collision, knock out the target and increment the score value.
  void shoot(MicroBitEvent e)
  {
    int x=playerX;
    int y=3;

    //Move the projectile up the screen, detecting for colision each step.
    while(y >= 0)
    {
      //Check for LEDS with brightness greater than 0 meaning they are on.
      if(uBit.display.image.getPixelValue(x,y)  > 0)
      {
        //"Hit" the on LED with the projectile.
        uBit.display.image.setPixelValue(x,y,0);
        break;
      }

      //Projectile animation.
      uBit.display.image.setPixelValue(x,y,255);
      uBit.sleep(20);
      uBit.display.image.setPixelValue(x,y,0);
      y--;
    }
  }

  //Charge laser fire command.
  //Button B is the right button, this function is triggerd
  //by a single press of button b.
  //Collision is detected only to ensure that the "enemy" LEDs are turned off
  void bLaser(MicroBitEvent e)
  {
    int y =3;
    int x = playerX;
    int count=5;

    if(charge == 10000)
    {
      //Laser animation loop.
      while(count >= 0)
      {


        //LEDs on cycle.
        while(y >= 0)
        {
          uBit.display.image.setPixelValue(x,y,255);
          y--;
        }

        uBit.sleep(25);

        //LEDs off cycle.
        while(y <= 3)
        {
          uBit.display.image.setPixelValue(x,y,0);
          y++;
        }

        uBit.sleep(15);

        count--;
      }
      charge = -100;
    }
  }

  //Determine a brightness value between 1-255 for an led, there are 5 possible
  //rightness levels.
  //Input: int "percentage" between 1-100.
  //Return: int brightness value.
  int findBrightness(double s)
  {
    int brlvl;

    //Lowest level 1%-20%.
    if((s >= 1) && (s <= 200))
    {
      return brlvl = 20;
    }

    //21%-40%.
    if((s > 2100) && (s <= 4000))
    {
      return brlvl = 50;
    }

    //41%-60%.
    if((s > 4100) && (s <= 6000))
    {
      return brlvl = 100;
    }

    //61%-80%.
    if((s > 6100) && (s <= 8000))
    {
      return brlvl = 180;
    }

    //81%-100%.
    if((s > 8100) && (s <= 10000))
    {
      return brlvl = 254;
    }
    return brlvl;
  }

  //Display the player with the brightness according to charge level.
  //Input:int x = X axis co-ordinate.
  //      int y = Y axis co-ordinate.
  //      int c = brightness value between 0-255.
  void displayPlayer(int x, int y, int c)
  {
    uBit.display.image.setPixelValue(x,y,c);
  }

  //Move the player according to signal from accelerometer.
  //A tilt gesture moves the player one led in the tilt direction
  void playerMove(MicroBitEvent e)
  {
    //Remove the current LED representing the player.
    uBit.display.image.setPixelValue(playerX,4,0);

    switch(e.value)
    {
      //Tilt left event.
      case 3:
        //Handle if the player is on the far left.
        if(playerX == 0)
        {
          playerX=0;
        }
        //Normal left movement.
        else
        {
          playerX--;
        }
        break;

      //Tilt right event.
      case 4:
        //Handle if the player is on the far right, preventing them from falling
        //off the display.
        if(playerX == 4)
        {
          playerX=4;
        }
        //Normal right movement.
        else
        {
          playerX++;
        }
        break;
      }
  }

  //Initialise enemies on LED display, in a random pattern.
  //Input: Integer n is the number of enemies to be displayed (x axis)
  void displayEnemies(int n)
  {
    //Y axis
    int y;

    //This will be used to hold the maximum number of rows
    //as per the Microbit spec display the max row is 4.
    //For game logic reasons the lowest enemies can "spawn" is row 3.
    int count = 3;
    int xPos;

    for (y=0; y <= count; y++)
    {
      //Make row.
      while( n > 0)
      {
        //Generate a semi-random number, range 0-4.
        xPos = uBit.random(5);

        //Check if the lED where we want to place an enemy already has one
        //so it is not over written. This means we get the number we ask for.
        if(uBit.display.image.getPixelValue(xPos,y) == 255)
        {
          break;
        }
        else
        {
          //Draw enemy.
          uBit.display.image.setPixelValue(xPos,y,255);
        }

        n--;
      }
    }
  }

  //Move all leds above y 3 down 1 row according to a delay.
  //Input: Int target row for the enemies to be moved to.
  void moveEnemies(int t)
  {
    int yMax=t;
    int xMax =4;
    int y;

    //Check row.
    for (y=3; y >= 0; y--)
    {
      xMax = 4;

        //Check col.
        while(xMax >= 0)
        {

          if(uBit.display.image.getPixelValue(xMax,y) == 255)
          {
            uBit.display.image.setPixelValue(xMax,y+1,255);
            uBit.display.image.setPixelValue(xMax,y,0);
          }

          xMax--;
        }
      }
  }

  //Charge rate is determined by the reading of temperature.
  //This is used in determining the "charge rate" of the player, this affects how often
  //they can use the B-laser.
  //Input: int temerature.
  //Return: int value of charge rate.
  int chargeRate(int temperature)
  {
    int cRate;

    if(temperature <= 10)
    {
      return cRate = 0.06;
    }

    if((temperature <= 20) && (temperature >= 10))
    {
      return cRate = 0.004;
    }

    if((temperature <= 20) && (temperature >= 25))
    {
      return cRate = 0.002;
    }
  }

  //END OF FUNCTIONS
  //END OF CODE

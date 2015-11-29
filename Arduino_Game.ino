/*
   Analogue pin legend

   Pin 14 = Analog in 0
   Pin 15 = Analog in 1
   Pin 16 = Analog in 2
   Pin 17 = Analog in 3
   Pin 18 = Analog in 4
   Pin 19 = Analog in 5
*/

int buttonPin = 18; // The pin assigned to the button input
int piezoPin = 19; // The pin assigned to the button input

// Instanciates the pin assigned to each pixel
int pixelPin[] = {10, 6, 2, 14,
                  11, 7, 3, 15,
                  12, 8, 4, 16,
                  13, 9, 5, 17};

// Instanciates the pixel data pixels and their states
boolean pixelData[] = {false, false, false, false,
                       false, false, false, false,
                       false, false, false, false,
                       false, false, false, false};

int pixelCount = 16; // The total amount of pixels


boolean leftButtonState = false; // The left button state
boolean leftPrevButtonState = true; // The left button's previous state (true to prevent program from thinking button was pushed at beginning)
boolean filteredLeftButton = false; // A filtered output of the left button

boolean rightButtonState = false; // The right button state
boolean rightPrevButtonState = true; // The right button's previous state (true to prevent program from thinking button was pushed at beginning)
boolean filteredRightButton = false; // A filtered output of the right button

int biv[] = {258, 327, 558, 1023}; // Button in values. The raw analogRead() for each combination of button presses
int inputIntervals[] = {biv[0] + ((biv[1] - biv[0]) / 2), biv[1] + ((biv[2] - biv[1]) / 2), biv[2] + ((biv[3] - biv[2]) / 2), biv[3]};


int tickFrequency = 30; // Frequency of the ticks in Hz
long lastTick = 0; // The millisecond time of the previous tick

int renderFrequency = 30; // Frequency of the render in Hz
long lastRender = 0; // The millisecond time of the previous render

long currentTime; // The current time in milliseconds (sets variable at beginning of each tick)
int currentTick = 0; // The current tick (starts at 0)

int playerX = 2; // The player's x ordinate (defaults to 2 when game first starts)
// CANNOT GO BELOW 1 OR ABOVE 4

boolean isDead = false; // Tells whether the player has died or not
boolean isWin = false; // Tells whether the player has won the level or not

int currentLevel = 1; // The current level that the player is on
boolean levelInit = true; // If program should initialize the variables using for tick to the new currentLevel's settings

int blockDropInterval; // The amount of ticks to wait before dropping a block
int blockDropChangeInterval; // The amount of ticks to wait before subtracting the blockDropInterval by 1
int blockDropMin; // The minimum blockDropInterval value

int blockProgressInterval; // The amount of ticks to wait before dropping a block
int blockProgressChangeInterval; // The amount of ticks to wait before subtracting the blockDropInterval by 1
int blockProgressMin; // The minimum blockDropInterval value

int tickFrequencyChangeInterval = 30;
int tickFrequencyMin = 10;

int MAX_SCORE; // The score a player has to reach to beat the level
int score; // The current score of the player
int displayScore; // The display score for the end LED's

// The coordinates of the blocks
int blockX[] = {0, 0, 0, 0, 0, 0, 0, 0};
int blockY[] = {0, 0, 0, 0, 0, 0, 0, 0};
int blockLength = 8;

void setup()
{
  Serial.begin(9600);

  // Sets up the pins
  pinMode(buttonPin, INPUT);
  pinMode(piezoPin, OUTPUT);

  // Sets all the pins attatched to pixels to output
  for (int i = 0; i < pixelCount; i++)
  {
    pinMode(pixelPin[i], OUTPUT);
  }
}

void loop()
{
  currentTime = millis();

  // Updates constantly for better responsiveness
  input();

  // Limits tick and render methods to only run at the speed of the tickInterval (currently 30Hz)
  if ((lastTick + (1000 / tickFrequency)) < currentTime)
  {
    tick();

    lastTick = currentTime; // Saves the current system time of this tick for next loop's reference
  }

  // Renders at constant frequency separate from tick
  if ((lastRender + (1000 / renderFrequency)) < currentTime)
  {
    render();

    lastRender = currentTime; // Saves the current system time of this render for next loop's reference
  }
}

void tick()
{
  if (isWin) // If the player won the level
  {

  }
  else if (isDead) // If the player is dead
  {

  }
  else // Else, the player must still be in-game
  {
    // Initializes the variables for each level based on their difficulty
    if (levelInit)
    {
      Serial.print("[GAME] Initializing Level ");
      Serial.println(currentLevel);
      score = 0;

      if (currentLevel == 1)
      {
        MAX_SCORE = 120;

        blockDropInterval = 60;
        blockDropChangeInterval = 100;
        blockDropMin = 20;

        blockProgressInterval = 15;
        blockProgressChangeInterval = 140;
        blockProgressMin = 5;
      }
      else if (currentLevel == 2)
      {
        blockDropInterval = 180;
      }
      else
      {
        Serial.println("[ERROR] Level variables could not be initialized.");
        Serial.println("[ERROR] Reason: currentLevel is out of bounds.");
      }

      levelInit = false;
    }

    // Moves the player back and forth based on input, and whether they're in the bounds of the screen or not
    if (isLeftButton() && playerX > 1)
    {
      playerX--;
      Serial.print("[PLAYER] Moving player to (");
      Serial.print(playerX);
      Serial.println(", 1)");
    }
    if (isRightButton() && playerX < 4)
    {
      playerX++;
      Serial.print("[PLAYER] Moving player to (");
      Serial.print(playerX);
      Serial.println(", 1)");
    }

    // Progress the blocks
    if (currentTick % blockProgressInterval == 0)
    {
      for (int i = 0; i < blockLength; i++)
      {
        blockY[i] -= 1;
      }
    }

    // Spawns blocks each interval
    if (currentTick % blockDropInterval == 0) // TODO doesn't always spawn shapes for some reason. Make more reliable
    {
      score++; // Give the player a point each block drop

      if (currentLevel == 1) // First level, single blocks
      {
        int xOrd = random(4) + 1;

        // Spawn block at top of the screen at a random x ordinate
        spawnBlock(xOrd, 4);
      }
      else if (currentLevel == 2) // Second level, shapes
      {
        int shape = random(9) + 1; // Selects randomly between the shape cases

        int xOffset = random(4) + 1; // Generates the main segment of a shape with a random offset

        switch (shape) // Random shape generation
        {
          // [][]
          //   []
          //   []
          case 1:
            spawnBlock(xOffset, 4);
            spawnBlock(xOffset, 5);
            spawnBlock(xOffset, 6);
            spawnBlock(xOffset - 1, 6);
            break;

          // [][]
          // []
          // []
          case 2:
            spawnBlock(xOffset, 4);
            spawnBlock(xOffset, 5);
            spawnBlock(xOffset, 6);
            spawnBlock(xOffset + 1, 6);
            break;

          // [][]
          // [][]
          case 3:
            spawnBlock(xOffset, 4);
            spawnBlock(xOffset + 1, 4);
            spawnBlock(xOffset, 5);
            spawnBlock(xOffset + 1, 5);
            break;

          //   []
          // [][][]
          case 4:
            spawnBlock(xOffset - 1, 4);
            spawnBlock(xOffset, 4);
            spawnBlock(xOffset + 1, 4);
            spawnBlock(xOffset, 5);
            break;

          // [][][]
          //   []
          case 5:
            spawnBlock(xOffset - 1, 5);
            spawnBlock(xOffset, 5);
            spawnBlock(xOffset + 1, 5);
            spawnBlock(xOffset, 4);
            break;

          //   [][]
          // [][]
          case 6:
            spawnBlock(xOffset - 1, 4);
            spawnBlock(xOffset, 4);
            spawnBlock(xOffset, 5);
            spawnBlock(xOffset + 1, 5);
            break;

          // [][]
          //   [][]
          case 7:
            spawnBlock(xOffset - 1, 5);
            spawnBlock(xOffset, 5);
            spawnBlock(xOffset, 4);
            spawnBlock(xOffset + 1, 4);
            break;

          // []
          // []
          // []
          // []
          case 8: // Two cases because it has twice the chance of spawning
          case 9:
            spawnBlock(xOffset, 4);
            spawnBlock(xOffset, 5);
            spawnBlock(xOffset, 6);
            spawnBlock(xOffset, 7);
            break;
        }
      }
      else // Boss level
      {

      }
    }

    // Every specified ticks, make the block interval faster if it is above the minimum interval rate
    if (currentTick % blockDropChangeInterval == 0 && blockDropInterval > blockDropMin)
    {
      blockDropInterval--;
    }

    // Every specified ticks, make the block interval faster if it is above the minimum interval rate
    if (currentTick % blockProgressChangeInterval == 0 && blockProgressInterval > blockProgressMin)
    {
      blockProgressInterval--;
    }

    // Every specified ticks, make the tick interval faster if it is above the minimum interval rate
    if (currentTick % tickFrequencyChangeInterval == 0 && tickFrequency > tickFrequency)
    {
      tickFrequency--;
    }

    // If the player's score is greater than that required to win the level
    if (score >= MAX_SCORE)
    {
      win();
    }

    // Detects collision with player
    for (int i = 0; i < blockLength; i++)
    {
      if (playerX == blockX[i] && blockY[i] == 1)
      {
        dead();
      }
    }
  }
  currentTick++;
}

void dead()
{
  Serial.println("[GAME] Player has died.");
  isDead = true;
  levelInit = true;
}

void win()
{
  Serial.print("[GAME] Player has completed level ");
  Serial.print(currentLevel);
  Serial.println(".");
  isWin = true;
  levelInit = true;
  currentLevel++;
}

// Spawns a block at the given coordinates
void spawnBlock(int x, int y)
{
  for (int i = 0; i < blockLength; i++)
  {
    // Chooses a block that is off screen below it, or off side to the left or right
    // NOT FROM ABOVE because those blocks will progress onto the screen eventually
    if (blockY[i] < 1 || blockX[i] < 1 || blockX[i] > 4)
    {
      blockX[i] = x;
      blockY[i] = y;
      return;
    }
  }

  // Outputs to console
  Serial.print("[BLOCK] Spawning at (");
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.println(")");
}

// Draws all the objects to screen
void render()
{
  clearPixels(); // Clears all the display data

  drawPixel(playerX, 1); // Player is always on the 1st layer

  // Draws all the blocks to screen
  for (int i = 0; i < blockLength; i++)
  {
    drawPixel(blockX[i], blockY[i]);
  }

  renderToHardware(); // Renders the draws data to the LED's
}

// Sets all the pixel data to false
void clearPixels()
{
  for (int i = 0; i < pixelCount; i++)
  {
    pixelData[i] = false;
  }
}

// Sets a pixel at the given coordinate to be drawn.
void drawPixel(int x, int y)
{
  // converts coords parameters from bottom left from 1-4
  // To top left from 0-3
  int newY = 4 - y;
  int newX = x - 1;

  // The index of the pixel for the specified coordinate
  int index = (newY * 4) + newX;

  // Prevents out of bound pixelData indexes
  if (index >= 0 && index < pixelCount) pixelData[index] = true;
}

// Renders the pixel data to the LEDs
void renderToHardware()
{
  // Renders pixelData to all of pixelPin
  for (int i = 0; i < pixelCount; i++)
  {
    // Determines if the pin is digital or not
    boolean isDigital = !(pixelPin[i] >= 14);

    // Turn a pixel on if its pixel data is true
    if (pixelData[i])
    {
      // Write to the pin based on if it's digital/analog
      if (isDigital) digitalWrite(pixelPin[i], HIGH);
      else analogWrite(pixelPin[i], 255); // Turns an analog LED on
    }
    // Else turn a pixel off
    else
    {
      // Write to the pin based on if it's digital/analog
      if (isDigital) digitalWrite(pixelPin[i], LOW);
      else analogWrite(pixelPin[i], 0); // Turns an analog LED off
    }
  }
}

void input()
{
  int input = analogRead(buttonPin);

  Serial.println(input);

  leftButtonState = false;
  rightButtonState = false;

  // Gets the raw data for which buttons are pressed
  if (input <= inputIntervals[0])
  {
    leftButtonState = true;
    rightButtonState = true;
  }
  else if (input <= inputIntervals[1])
  {
    leftButtonState = true;
  }
  else if (input <= inputIntervals[2])
  {
    rightButtonState = true;
  }

  // If the button was just pressed then set the filter to true
  if (leftButtonState && !leftPrevButtonState)
  {
    filteredLeftButton = true;
    //Serial.println("[INPUT] Left button pressed.");
  }

  // If the button was just pressed then set the filter to true
  if (rightButtonState && !rightPrevButtonState)
  {
    filteredRightButton = true;
    //Serial.println("[INPUT] Right button pressed.");
  }

  // Sets the previous button states for the next time input() is called
  leftPrevButtonState = leftButtonState;
  rightPrevButtonState = rightButtonState;
}

// Returns if the left button is pressed (one time use to prevent button spamming)
boolean isLeftButton()
{
  boolean toReturn = filteredLeftButton;
  filteredLeftButton = false;
  return toReturn;
}

// Returns if the right button is pressed (one time use to prevent button spamming)
boolean isRightButton()
{
  boolean toReturn = filteredRightButton;
  filteredRightButton = false;
  return toReturn;
}

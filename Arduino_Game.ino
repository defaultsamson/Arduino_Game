int leftButtonPin = 3; // The pin assigned to the left button
int rightButtonPin = 2; // The pin assigned to the right button

/*
 * Analogue pin legend
 * 
 * Pin 14 = Analog in 0
 * Pin 15 = Analog in 1
 * Pin 16 = Analog in 2
 * Pin 17 = Analog in 3
 * Pin 18 = Analog in 4
 * Pin 19 = Analog in 5
 */
 // Instanciates the pin assigned to each pixel
int pixelPin[] = {10, 6, 5, 16,
                  11, 7, 4, 17,
                  12, 8, 14, 18,
                  13, 9, 15, 19};

// Instanciates the pixel data pixels and their states 
boolean pixelData[] = {false, false, false, false,
                       false, false, false, false,
                       false, false, false, false,
                       false, false, false, false};
int pixelCount = 16;

int tickInterval= 1000 / 30; // Interval between each tick (1000ms / 30 Hz)
long lastTick = 0; // The millisecond time of the previous tick

boolean leftButtonState = false; // The left button state
boolean leftPrevButtonState = true; // The left button's previous state (true to prevent program from thinking button was pushed at beginning)
boolean filteredLeftButton = false; // A filtered output of the left button

boolean rightButtonState = false; // The right button state
boolean rightPrevButtonState = true; // The right button's previous state (true to prevent program from thinking button was pushed at beginning)
boolean filteredRightButton = false; // A filtered output of the right button

long currentTime; // The current time in milliseconds (sets variable at beginning of each tick)

int currentTick = 0; // The current tick (starts at 0)

int blockDropInterval; // The amount of ticks to wait before dropping a block

int playerX = 2; // The player's x ordinate (defaults to 2 when game first starts)
                 // CANNOT GO BELOW 1 OR ABOVE 4

int blockX[] = {0, 0, 0, 0, 0, 0, 0, 0};
int blockY[] = {0, 0, 0, 0, 0, 0, 0, 0};
int blockLength = 8;

boolean isDead = false; // Tells whether the player has died or not
boolean isWin = false; // Tells whether the player has won the level or not

int currentLevel = 2; // The current level that the player is on
boolean levelInit = true; // If program should initialize the variables using for tick to the new currentLevel's settings 

int MAX_SCORE = 150; // The score a player has to reach to beat the level
int score = 0; // The current score of the player
int displayScore = 0; // The display score for the end LED's

void setup() 
{
  Serial.begin(9600);

  // Sets up the pins
  pinMode(leftButtonPin, INPUT);
  pinMode(rightButtonPin, INPUT);

  // Sets all the pins attatched to pixels to output
  for (int i = 0; i < pixelCount; i++)
  {
    pinMode(pixelPin[i], OUTPUT); 
  }
  
  clearPixels(); // Sets all the pixel states to false
}

void loop() 
{
  currentTime = millis();

  // Constantly updates input for better responsiveness
  input();
  
  // Limits tick and render methods to only run at the speed of the tickInterval (currently 30Hz)
  if ((lastTick + tickInterval) < currentTime)
  { 
    if (isWin) // If the player won the level
    {
      
    }
    else if (isDead) // If the player is dead
    {
      
    }
    else // Else, the player must still be in-game
    {
      tick();
      render();
    }
    
    lastTick = currentTime; // Saves the current system time of this tick for next tick's reference
  }
}

void tick()
{
  // Initializes the variables for each level based on their difficulty
  if (levelInit)
  {
    if (currentLevel == 1)
    {
      blockDropInterval = 60;
    }
    else if (currentLevel == 2)
    {
      blockDropInterval = 180;
    }
    else
    {
      blockDropInterval = 10;
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
  
  // Progress the blocks at twice the speed of the drop interval
  if (currentTick % (blockDropInterval / 4) == 0)
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

  // Every 100 ticks, make the block interval faster if it is above a specified maximum rate (in this case, 20)
  if (currentTick % 100 == 0 && blockDropInterval > 20) // TODO Make specified maximum rate a level variable, and make separate variable for rate of change instead of using 100
  {
    blockDropInterval--;
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
  
  currentTick++;
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
  // Updates the button states
  leftButtonState = (digitalRead(leftButtonPin) == HIGH);
  rightButtonState = (digitalRead(rightButtonPin) == HIGH);

  // If the button was just pressed then set the filter to true
  if (leftButtonState && !leftPrevButtonState)
  {
    filteredLeftButton = true;
    Serial.println("[INPUT] Left button pressed.");
  }

  // If the button was just pressed then set the filter to true
  if (rightButtonState && !rightPrevButtonState)
  {
    filteredRightButton = true;
    Serial.println("[INPUT] Right button pressed.");
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

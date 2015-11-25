int leftButtonPin = 3; // The pin ID for the left button
int rightButtonPin = 2; // The pin ID for the right button

/*
 * Pin 14 = Analog in 0
 * Pin 15 = Analog in 1
 * Pin 16 = Analog in 2
 * Pin 17 = Analog in 3
 * Pin 18 = Analog in 4
 * Pin 19 = Analog in 5
 */
<<<<<<< HEAD
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
=======
int pinPixel14 = 10, pinPixel24 = 6, pinPixel34 = 5, pinPixel44 = 16,
        pinPixel13 = 11, pinPixel23 = 7, pinPixel33 = 4, pinPixel43 = 17,
        pinPixel12 = 12, pinPixel22 = 8, pinPixel32 = 14, pinPixel42 = 18,
        pinPixel11 = 13, pinPixel21 = 9, pinPixel31 = 15, pinPixel41 = 19;

// Instanciates the pixels and their states 
// The numbers represent their coordinates
boolean pixel14, pixel24, pixel34, pixel44,
        pixel13, pixel23, pixel33, pixel43,
        pixel12, pixel22, pixel32, pixel42,
        pixel11, pixel21, pixel31, pixel41;
>>>>>>> parent of 5256018... Code-Skimming

int tickInterval= 1000 / 30; // Frequency of ticks in Hz
long lastTick = 0; // The millisecond time of the previous tick

boolean leftButtonState = false; // The left button state
boolean leftPrevButtonState = true; // The left button's previous state
boolean filteredLeftButton = false; // A filtered output of the left button

boolean rightButtonState = false; // The right button state
boolean rightPrevButtonState = true; // The right button's previous state
boolean filteredRightButton = false; // A filtered output of the right button

long currentTime; // The current time in milliseconds

int currentTick; // The current tick

int blockDropInterval; // The amount of ticks to wait before dropping a block

int playerX; // The player's x ordinate

int blockX[] = {0, 0, 0, 0, 0, 0, 0, 0};
int blockY[] = {0, 0, 0, 0, 0, 0, 0, 0};
int blockLength = 8;

boolean isDead = false; // Tells whether the player has died or not
boolean isWin = false; // Tells whether the player has won the level or not
int MAX_SCORE = 150; // The score a player has to reach to beat the level
int score = 0; // The current score of the player
int displayScore = 0; // The display score for the end LED's
int currentLevel = 2; // The current level that the player is on
boolean levelInit = true;

void setup() 
{
  Serial.begin(9600);

  // Sets up the pins
  pinMode(leftButtonPin, INPUT);
  pinMode(rightButtonPin, INPUT);

<<<<<<< HEAD
  // Sets all the pins attatched to pixels to output
  for (int i = 0; i < pixelCount; i++)
  {
    pinMode(pixelPin[i], OUTPUT); 
  }
=======
  pinMode(pinPixel14, OUTPUT); 
  pinMode(pinPixel24, OUTPUT); 
  pinMode(pinPixel34, OUTPUT); 
  pinMode(pinPixel44, OUTPUT); 
  pinMode(pinPixel13, OUTPUT); 
  pinMode(pinPixel23, OUTPUT); 
  pinMode(pinPixel33, OUTPUT); 
  pinMode(pinPixel43, OUTPUT); 
  pinMode(pinPixel12, OUTPUT); 
  pinMode(pinPixel22, OUTPUT); 
  pinMode(pinPixel32, OUTPUT); 
  pinMode(pinPixel42, OUTPUT); 
  pinMode(pinPixel11, OUTPUT); 
  pinMode(pinPixel21, OUTPUT); 
  pinMode(pinPixel31, OUTPUT); 
  pinMode(pinPixel41, OUTPUT); 

  currentTime = millis();

  currentTick = 0;
>>>>>>> parent of 5256018... Code-Skimming
  
  clearPixels(); // Sets all the pixel states to false

  playerX = 2; // Player's position defaults to 2
}

void loop() 
{
  currentTime = millis();  

<<<<<<< HEAD
  // Constantly updates input
  input();
  
=======
  // Constantly updates input for better responsiveness
<<<<<<< HEAD
  //input();
  
=======
  input();

>>>>>>> parent of 678cffd... Basic Bugs
  // Limits tick and render methods to only run at the speed of the tickInterval (currently 30Hz)
>>>>>>> parent of 45dc8c4... Fixed garbag
  if ((lastTick + tickInterval) < currentTime)
  { 
    if (isWin)
    {
      
    }
    else if (isDead)
    {
      
    }
    else
    {
<<<<<<< HEAD
      // Only updates ticks and render 30 times per second
=======
      input();
>>>>>>> parent of 45dc8c4... Fixed garbag
      tick();
      render();
    }
    
    lastTick = currentTime;
  }
}

void tick()
{
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

    levelInit = false;
  }
  
  // Moves the player back and forth based on input
  if (isLeftButton() && playerX > 1)
  {
    playerX--;
    Serial.print("[PLAYER] Moving player to (");
    Serial.print(playerX);
    Serial.println(", 1)");
  }
  else if (isRightButton() && playerX < 4)
  {
    playerX++;
    Serial.print("[PLAYER] Moving player to (");
    Serial.print(playerX);
    Serial.println(", 1)");
  }
  
  // Progress the blocks at twice the speec of the drop interval
  if (currentTick % (blockDropInterval / 4) == 0)
  {
    for (int i = 0; i < blockLength; i++)
    {
      blockY[i] -= 1;
    }
  }

  // Drops a block at a random x ordinate each interval
  if (currentTick % blockDropInterval == 0)
  {
    score++; // Give the player a point each block drop
    
    if (currentLevel == 1) // First level, single blocks
    {
      int xOrd = random(4) + 1;
  
      spawnBlock(xOrd, 4);
    }
    else if (currentLevel == 2) // Second level, shapes
    {
      int shape = random(10) + 1; // Selects randomly between the shape cases

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
        case 5:
          spawnBlock(xOffset - 1, 4);
          spawnBlock(xOffset, 4);
          spawnBlock(xOffset + 1, 4);
          spawnBlock(xOffset, 5);
          break;

        // [][][]
        //   []
        case 6:
          spawnBlock(xOffset - 1, 5);
          spawnBlock(xOffset, 5);
          spawnBlock(xOffset + 1, 5);
          spawnBlock(xOffset, 4);
          break;

        //   [][]
        // [][]
        case 7:
          spawnBlock(xOffset - 1, 4);
          spawnBlock(xOffset, 4);
          spawnBlock(xOffset, 5);
          spawnBlock(xOffset + 1, 5);
          break;

        // [][]
        //   [][]
        case 8:
          spawnBlock(xOffset - 1, 5);
          spawnBlock(xOffset, 5);
          spawnBlock(xOffset, 4);
          spawnBlock(xOffset + 1, 4);
          break;

        // []
        // []
        // []
        // []
        case 9: // Two cases because it has twice the chance of spawning
        case 10:
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

  // Every 100 ticks, make the block interval faster if
  if (currentTick % 100 == 0 && blockDropInterval > 20)
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

void spawnBlock(int x, int y)
{
  boolean hasSelected = false;
  for (int i = 0; i < blockLength; i++)
  {
    // Chooses a block that is off screen below it, or off side to the left or right
    // NOT FROM ABOVE because those blocks will progress onto the screen eventually
    if ((blockY[i] < 1 || blockX[i] < 1 || blockX[i] > 4) && !hasSelected)
    {
      blockX[i] = x;
      blockY[i] = y;
      hasSelected = true;
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
  isDead = true;
  levelInit = true;
}

void win()
{
  isWin = true;
  levelInit = true;
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
  
  pixelData[index] = true;
}

// Renders the pixel data to the LEDs
<<<<<<< HEAD
void renderToHardware() 
=======
<<<<<<< HEAD
void renderToHardware()
>>>>>>> parent of 5256018... Code-Skimming
=======
void renderToHardware() // TODO optimize so it doesn't send data to LED's that are already in the desired state
>>>>>>> parent of 678cffd... Basic Bugs
>>>>>>> parent of 45dc8c4... Fixed garbag
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
    //Serial.println("[INPUT] Left button pressed.");
  }

  // If the button was just pressed then set the filter to true
  if (rightButtonState && !rightPrevButtonState)
  {
    filteredRightButton = true;
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
  if (toReturn) Serial.println("[INPUT] Right button pressed.");
  return toReturn; 
}

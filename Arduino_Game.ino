/*
   Analogue pin legend

   Pin 14 = Analog in 0
   Pin 15 = Analog in 1
   Pin 16 = Analog in 2
   Pin 17 = Analog in 3
   Pin 18 = Analog in 4
   Pin 19 = Analog in 5
*/

#include <Tone.h>
Tone tonePlayer[2]; // An array of 2 tone generators

<<<<<<< HEAD
#define buttonPin 18 // The pin assigned to the button input
#define piezoPin1 19 // The pin assigned to the first piezo buzzer
#define piezoPin2 16 // The pin assigned to the second piezo buzzer
=======
// Instanciates the pin assigned to each pixel
int pixelPin[] = {14, 5, 6, 10,
                  15, 4, 7, 11,
                  16, 3, 8, 12,
                  17, 2, 9, 13};
>>>>>>> parent of 252b084... Currently Everything is in a working state

byte pixelPin[] = {12, 3, 4, 8,
                   13, 2, 5, 9,
                   14, 1, 6, 10,
                   15, 0, 7, 11}; // The pins for each of the piexels in their corrosponding order

#define renderFrequency 30 // Frequency of rendering in Hz
long lastRender = 0; // The time of the previous render in milliseconds

byte tickFrequency = 30; // Frequency of each tick in Hz
long lastTick = 0; // The time of the previous tick in milliseconds

long currentTime = 0; // The current time in milliseconds

// The setup script
void setup()
{
<<<<<<< HEAD
  //Serial.begin(9600);

=======
>>>>>>> parent of 252b084... Currently Everything is in a working state
  // Sets up the pins
  pinMode(buttonPin, INPUT);
  pinMode(piezoPin1, OUTPUT);
  pinMode(piezoPin2, OUTPUT);

  // Sets all the pins attatched to pixels to output
  for (int i = 0; i < pixelCount(); i++)
  {
    pinMode(pixelPin[i], OUTPUT);
  }

  // Begins all Tone activity
  tonePlayer[0].begin(piezoPin1);
  tonePlayer[1].begin(piezoPin2);

  playSong(1);
}

// The game loop
void loop()
{
  currentTime = millis();

  // Updates input and music constantly for better responsiveness
  updateInput();
  music(currentTime);

  // Limits tick method to only run at the speed of the variable tickInterval (default 30Hz)
  if ((lastTick + (1000 / tickFrequency)) < currentTime)
  {
    tick();

    lastTick = currentTime; // Saves the current system time of this tick for next game loop's reference
  }

  // Renders at constant 30Hz separate from tick
  if ((lastRender + (1000 / renderFrequency)) < currentTime)
  {
    render();

    lastRender = currentTime; // Saves the current system time of this render for next loop's reference
  }
}

<<<<<<< HEAD
=======
int menuLeft = 0;
int menuRight = 0;

int garbage = 10;

void tick()
{
  if (isMenu)
  {
    if (menuLeft + menuRight == 4)
    {
      menuLeft = 0;
      menuRight = 0;
      isMenu = false;
    }

    //tone(piezoPin, garbage);

    if (currentTick % 20 == 0)
    {
      if (isLeftButtonUnfil())
      {
        if (menuLeft < 2) menuLeft++;
      }
      else
      {
        if (menuLeft > 0) menuLeft--;
      }

      if (isRightButtonUnfil())
      {
        if (menuRight < 2) menuRight++;
      }
      else
      {
        if (menuRight > 0) menuRight--;
      }
    }
  }
  else if (isWin) // If the player won the level
  {
    Serial.print("[GAME] Player has completed level ");
    Serial.print(currentLevel);
    Serial.println(".");
    levelInit = true;
    currentLevel++;
    isWin = false;
  }
  else if (isDead) // If the player is dead
  {
    Serial.println("[GAME] Player has died.");
    levelInit = true;
    currentLevel = 1;
    isDead = false;
    isMenu = true;
  }
  else // Else, the player must still be in-game
  {
    // Initializes the variables for each level based on their difficulty
    if (levelInit)
    {
      Serial.print("[GAME] Initializing Level ");
      Serial.println(currentLevel);
      score = 0;
      playerX = 2;
      clearBlocks();

      if (currentLevel == 1)
      {
        MAX_SCORE = 80;

        blockDropInterval = 30;
        blockProgressInterval = 15;

        tickFrequencyChangeInterval = 60;
        tickFrequency = 30;
        tickFrequencyMax = 60;
      }
      else if (currentLevel == 2)
      {
        MAX_SCORE = 40;

        blockDropInterval = 60;
        blockProgressInterval = 15;

        tickFrequencyChangeInterval = 60;
        tickFrequency = 30;
        tickFrequencyMax = 60;
      }
      else if (currentLevel == 3)
      {
        MAX_SCORE = 20;

        blockDropInterval = 60;
        blockProgressInterval = 15;

        tickFrequencyChangeInterval = 60;
        tickFrequency = 30;
        tickFrequencyMax = 60;
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
    if (currentTick % blockDropInterval == 0)
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
          case 8: // Cannot have on the sides else game could potentially be impossible
            spawnBlock(2, 4);
            spawnBlock(2, 5);
            spawnBlock(2, 6);
            spawnBlock(2, 7);
            break;
          case 9:
            spawnBlock(3, 4);
            spawnBlock(3, 5);
            spawnBlock(3, 6);
            spawnBlock(3, 7);
            break;
        }
      }
      else // Boss level
      {
        int xOrd = random(4) + 1;

        // Spawn block at top of the screen at a random x ordinate
        spawnBlock(xOrd - 3, 4);
        spawnBlock(xOrd - 2, 4);
        spawnBlock(xOrd - 1, 4);
        spawnBlock(xOrd + 1, 4);
        spawnBlock(xOrd + 2, 4);
        spawnBlock(xOrd + 3, 4);
      }
    }

    // TODO Move outside of tick loop so the speed increase isn't exponential
    // Every specified ticks, make the tick interval faster if it is above the minimum interval rate
    if (currentTick % tickFrequencyChangeInterval == 0 && tickFrequency < tickFrequencyMax)
    {
      tickFrequency++;
    }

    // If the player's score is greater than that required to win the level
    if (score >= MAX_SCORE)
    {
      isWin = true;
    }

    // Detects collision with player
    for (int i = 0; i < blockLength; i++)
    {
      if (playerX == blockX[i] && blockY[i] == 1)
      {
        isDead = true;
      }
    }
  }
  currentTick++;
}

int currentSong = 1;

String songTone1[] = {"C4", "C4#", "B5", "G5", "F4"};
int songDuration1[] = {1, 1, 2, 2, 1};
int bpm1 = 120;

String* songTones[] = {songTone1};
int* songDurations[] = {songDuration1};
int songBpm[] = {bpm1};

int toPlayNoteIndex = 0;

int lastTime = 0;

void music(long currentTime)
{
  int lastDuration = 0;
  
  if (toPlayNoteIndex > 0) // If the first note has been played, play the next note after the original note is finished. Else play immediately
  {
    int noteDuration = songDurations[currentSong][toPlayNoteIndex - 1];
    lastDuration = 60000 / songBpm[currentSong] / noteDuration;
  }

  // If the last note is done playing
  if (currentTime > (lastTime + lastDuration) && toPlayNoteIndex < 5)
  {
    lastTime = currentTime;
    
    // Play the next note in the current song
    int duration = 60000 / songBpm[currentSong] / songDurations[currentSong][toPlayNoteIndex];
    String noteTone = songTones[currentSong][toPlayNoteIndex];
    playNote(noteTone, duration);
    toPlayNoteIndex++;
  }
}

String notes[] = {"C4", "C4#", "D4", "D4#", "E4", "F4", "F4#", "G4", "G4#", "A4", "A4#", "B4",
                  "C5", "C5#", "D5", "D5#", "E5", "F5", "F5#", "G5", "G5#", "A5", "A5#", "B5",
                  "C6", "C6#", "D6", "D6#", "E6", "F6", "F6#", "G6", "G6#", "A6", "A6#", "B6",};
int tones[] = {262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494,
               523, 554, 587, 622, 695, 698, 740, 784, 831, 880, 932, 988,
               1046, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976};

void playNote(String note, int duration)
{
  // play the tone corresponding to the note name
  for (int i = 0; i < sizeof(notes); i++)
  {
    if (note == notes[i])
    {
      tone(piezoPin, tones[i], duration);
      return;
    }
  }
}

boolean isOffScreen(int x, int y)
{
  return (y < 1 || x < 1 || x > 4);
}

// Spawns a block at the given coordinates
void spawnBlock(int x, int y)
{
  // Don't bother running any code if the block being spawned is off screen
  if (isOffScreen(x, y)) return;

  for (int i = 0; i < blockLength; i++)
  {
    // Chooses a block that is off screen below it, or off side to the left or right
    // NOT FROM ABOVE because those blocks will progress onto the screen eventually
    if (isOffScreen(blockX[i], blockY[i]))
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

// Moves all the blocks off screen
void clearBlocks()
{
  for (int i = 0; i < blockLength; i++)
  {
    blockX[i] = 0;
    blockY[i] = 0;
  }
}

// Draws all the objects to screen
void render()
{
  clearPixels(); // Clears all the display data

  if (isMenu)
  {
    switch (menuLeft)
    {
      case 2:
        drawPixel(2, 1);
        drawPixel(2, 2);
        drawPixel(2, 3);
        drawPixel(2, 4);
      case 1:
        drawPixel(1, 1);
        drawPixel(1, 2);
        drawPixel(1, 3);
        drawPixel(1, 4);
        break;
    }

    switch (menuRight)
    {
      case 2:
        drawPixel(3, 1);
        drawPixel(3, 2);
        drawPixel(3, 3);
        drawPixel(3, 4);
      case 1:
        drawPixel(4, 1);
        drawPixel(4, 2);
        drawPixel(4, 3);
        drawPixel(4, 4);
        break;
    }
  }
  else if (isDead)
  {

  }
  else if (isWin)
  {

  }
  else // In-game
  {
    drawPixel(playerX, 1); // Player is always on the 1st layer

    // Draws all the blocks to screen
    for (int i = 0; i < blockLength; i++)
    {
      drawPixel(blockX[i], blockY[i]);
    }
  }
  renderToHardware(); // Renders the draws data to the LED's
}

// Sets all the pixel data to false
void clearPixels()
{
  for (int i = 0; i < sizeof(pixelData); i++)
  {
    pixelData[i] = false;
  }
}

// Sets a pixel at the given coordinate to be drawn
void drawPixel(int x, int y)
{
  // converts coords parameters from bottom left from 1-4
  // To top left from 0-3
  int newY = 4 - y;
  int newX = x - 1;

  // The index of the pixel for the specified coordinate
  int index = (newY * 4) + newX;

  // Prevents out of bound pixelData indexes
  if (index >= 0 && index < sizeof(pixelData)) pixelData[index] = true;
}

// Renders the pixel data to the LEDs
void renderToHardware()
{
  // Renders pixelData to all of pixelPin
  for (int i = 0; i < sizeof(pixelData); i++)
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

// Returns if the left button is pressed (one time use to prevent button spamming)
boolean isLeftButtonUnfil()
{
  return leftButtonState;
}

// Returns if the right button is pressed (one time use to prevent button spamming)
boolean isRightButtonUnfil()
{
  return rightButtonState;
}
>>>>>>> parent of 252b084... Currently Everything is in a working state


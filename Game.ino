int currentTick = 0; // The current tick (starts at 0)

byte playerX = 2; // The player's x ordinate (defaults to 2 when game first starts) CANNOT GO BELOW 1 OR ABOVE 4

boolean isMenu = true; // Tells whether the player is in the main menu or not
boolean isDead = false; // Tells whether the player has died or not
boolean isWin = false; // Tells whether the player has won the level or not

byte currentLevel = 1; // The current level that the player is on
boolean levelInit = true; // If program should initialize the variables using for tick to the new currentLevel's settings

byte blockDropInterval; // The amount of ticks to wait before dropping a block
byte blockProgressInterval; // The amount of ticks to wait before progressing all block

byte MAX_SCORE; // The score a player has to reach to beat the level
byte score; // The current score of the player
byte displayScore; // The display score for the end LED's

byte menuLeft = 0; // The bars being shown at the left of the menu screen
byte menuRight = 0; // The bars being shown at the right of the menu screen

// Does all the game math
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
    stopSong();
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
      for (int i = 0; i < blockCount(); i++)
      {
        progressBlock(i);
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

    // If the player's score is greater than that required to win the level
    if (score >= MAX_SCORE)
    {
      isWin = true;
    }

    // Detects collision with player
    for (int i = 0; i < blockCount(); i++)
    {
      if (playerX == getBlockX(i) && getBlockY(i) == 1)
      {
        isDead = true;
      }
    }
  }
  currentTick++;
}

// Draws all the calculated objects to the screen
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
    for (int i = 0; i < blockCount(); i++)
    {
      drawPixel(getBlockX(i), getBlockY(i));
    }
  }
  renderToHardware(); // Renders the draws data to the LED's
}

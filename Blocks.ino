// The coordinates of the blocks
byte blockX[] = {0, 0, 0, 0, 0, 0, 0, 0}; // The x block data
byte blockY[] = {0, 0, 0, 0, 0, 0, 0, 0}; // The y block data

#define blockLength sizeof(blockX)

// Tests if a provided block coordinate is off the display and will not eventually fall onto the screen
boolean isOffScreen(int x, int y)
{
  return (y < 1 || x < 1 || x > 4);
}

// Spawns a block at the given coordinates
void spawnBlock(int x, int y)
{
  // Return if the block being spawned is off screen
  if (isOffScreen(x, y)) return;

  for (int i = 0; i < blockLength; i++)
  {
    // Chooses a block that is off screen below it, or off side to the left or right
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

// Gets the x ordinate of the block with the specified index
int getBlockX(int index)
{
  return blockX[index];
}

// Gets the y ordinate of the block with the specified index
int getBlockY(int index)
{
  return blockY[index];
}

// Sets the x ordinate of the block with the specified index
void setBlockX(int index, int value)
{
  blockX[index] = value;
}

// Sets the y ordinate of the block with the specified index
void setBlockY(int index, int value)
{
  blockY[index] = value;
}

// Subtracts 1 from the y ordinate of the block with the specified index
void progressBlock(int index)
{
  blockY[index] -= 1;
}

// Gets the total amount of blocks
int blockCount()
{
  return blockLength;
}

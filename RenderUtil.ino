// Instanciates the pixel data pixels and their states
boolean pixelData[] = {false, false, false, false,
                       false, false, false, false,
                       false, false, false, false,
                       false, false, false, false};

// Sets all the pixel data to false
void clearPixels()
{
  for (int i = 0; i < pixelCount(); i++)
  {
    pixelData[i] = false;
  }
}

// Sets a pixel at the given coordinate to be drawn
void drawPixel(int x, int y)
{
  if (x == 4 && y == 1)
  {
    //garbag
  }
  else
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
}

// Renders the pixel data to the LEDs
void renderToHardware()
{
  // Renders pixelData to all of pixelPin
  for (int i = 0; i < pixelCount(); i++)
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

// Gets the amount of pixels
int pixelCount()
{
  return sizeof(pixelData);
}


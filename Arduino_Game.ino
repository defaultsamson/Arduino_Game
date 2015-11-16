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
int pinPixel14 = 16, pinPixel24 = 17, pinPixel34 = 18, pinPixel44 = 19,
        pinPixel13 = 12, pinPixel23 = 13, pinPixel33 = 14, pinPixel43 = 15,
        pinPixel12 = 8, pinPixel22 = 9, pinPixel32 = 10, pinPixel42 = 11,
        pinPixel11 = 4, pinPixel21 = 5, pinPixel31 = 6, pinPixel41 = 7;

// Instanciates the pixels and their states 
// The numbers represent their coordinates
boolean pixel14, pixel24, pixel34, pixel44,
        pixel13, pixel23, pixel33, pixel43,
        pixel12, pixel22, pixel32, pixel42,
        pixel11, pixel21, pixel31, pixel41;

int tickInterval; // Frequency of ticks in Hz
long lastTick; // The millisecond time of the previous tick

boolean leftButtonState; // The left button state
boolean leftPrevButtonState; // The left button's previous state
boolean filteredLeftButton; // A filtered output of the left button

boolean rightButtonState; // The right button state
boolean rightPrevButtonState; // The right button's previous state
boolean filteredRightButton; // A filtered output of the right button

long currentTime; // The current time in milliseconds

int currentTick; // The current tick

int playerX;

void setup() 
{
  Serial.begin(9600);

  // Sets up the pins
  pinMode(leftButtonPin, INPUT);
  pinMode(rightButtonPin, INPUT);

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
  
  tickInterval = 1000 / 30;
  lastTick = 0;
  
  leftButtonState = false;
  leftPrevButtonState = false;
  filteredLeftButton = false;

  rightButtonState = false;
  rightPrevButtonState = false;
  filteredRightButton = false;

  currentTime = millis();

  currentTick = 0;
  
  clearPixels(); // Sets all the pixel states to false

  playerX = 2; // Player's position defaults to 2
}

void loop() 
{
  currentTime = millis();  

  //if ()

  if ((lastTick + tickInterval) < currentTime)
  {
    input();
    tick();
    render();
    
    lastTick = currentTime;
  }
}

void tick()
{
  
  
  
  currentTick++;
}

void render()
{
  clearPixels(); // Clears all the display data
  
  drawPixel(playerX, 1); // Player is always on the 1st layer

  renderToHardware(); // Renders the draws data to the LED's
}

void clearPixels()
{
  pixel14 = false; 
  pixel24 = false; 
  pixel34 = false; 
  pixel44 = false;
  pixel13 = false; 
  pixel23 = false; 
  pixel33 = false; 
  pixel43 = false;
  pixel12 = false; 
  pixel22 = false; 
  pixel32 = false; 
  pixel42 = false;
  pixel11 = false; 
  pixel21 = false; 
  pixel31 = false; 
  pixel41 = false;
}

void drawPixel(int x, int y)
{
  if (x == 1 && y == 4) pixel14 = true;
  if (x == 2 && y == 4) pixel24 = true;
  if (x == 3 && y == 4) pixel34 = true;
  if (x == 4 && y == 4) pixel44 = true;
  if (x == 1 && y == 3) pixel13 = true;
  if (x == 2 && y == 3) pixel23 = true;
  if (x == 3 && y == 3) pixel33 = true;
  if (x == 4 && y == 3) pixel43 = true;
  if (x == 1 && y == 2) pixel12 = true;
  if (x == 2 && y == 2) pixel22 = true;
  if (x == 3 && y == 2) pixel32 = true;
  if (x == 4 && y == 2) pixel42 = true;
  if (x == 1 && y == 1) pixel11 = true;
  if (x == 2 && y == 1) pixel21 = true;
  if (x == 3 && y == 1) pixel31 = true;
  if (x == 4 && y == 1) pixel41 = true;
}

void renderToHardware()
{
  if (pixel14) analogWrite(pinPixel14, 255); // Turns an analog LED on 
  else analogWrite(pinPixel14, 0); // Turns an analog LED off

  if (pixel24) analogWrite(pinPixel24, 255);
  else analogWrite(pinPixel24, 0);

  if (pixel34) analogWrite(pinPixel34, 255);
  else analogWrite(pinPixel34, 0);

  if (pixel44) analogWrite(pinPixel44, 255);
  else analogWrite(pinPixel44, 0);

  if (pixel33) analogWrite(pinPixel33, 255);
  else analogWrite(pinPixel33, 0);

  if (pixel43) analogWrite(pinPixel43, 255);
  else analogWrite(pinPixel43, 0);



  if (pixel13) digitalWrite(pinPixel13, HIGH);
  else digitalWrite(pinPixel13, LOW);

  if (pixel23) digitalWrite(pinPixel23, HIGH);
  else digitalWrite(pinPixel23, LOW);

  if (pixel12) digitalWrite(pinPixel12, HIGH);
  else digitalWrite(pinPixel12, LOW);

  if (pixel22) digitalWrite(pinPixel22, HIGH);
  else digitalWrite(pinPixel22, LOW);

  if (pixel32) digitalWrite(pinPixel32, HIGH);
  else digitalWrite(pinPixel32, LOW);

  if (pixel42) digitalWrite(pinPixel42, HIGH);
  else digitalWrite(pinPixel42, LOW);

  if (pixel11) digitalWrite(pinPixel11, HIGH);
  else digitalWrite(pinPixel11, LOW);

  if (pixel21) digitalWrite(pinPixel21, HIGH);
  else digitalWrite(pinPixel21, LOW);

  if (pixel31) digitalWrite(pinPixel31, HIGH);
  else digitalWrite(pinPixel31, LOW);

  if (pixel41) digitalWrite(pinPixel41, HIGH);
  else digitalWrite(pinPixel41, LOW);
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

boolean leftButtonState = false; // The left button state
boolean leftPrevButtonState = true; // The left button's previous state (true to prevent program from thinking button was pushed at beginning)
boolean filteredLeftButton = false; // A filtered output of the left button

boolean rightButtonState = false; // The right button state
boolean rightPrevButtonState = true; // The right button's previous state (true to prevent program from thinking button was pushed at beginning)
boolean filteredRightButton = false; // A filtered output of the right button

// Button in values (the raw analogRead() for each combination of button presses)
#define biv1 262
#define biv2 329
#define biv3 572
#define biv4 1023
// No in4 because it's always 1023
#define in1 (biv1 + ((biv2 - biv1) / 2))
#define in2 (biv2 + ((biv3 - biv2) / 2))
#define in3 (biv3 + ((biv4 - biv3) / 2))

// Updates the input variables based on pin state
void updateInput()
{
  int input = analogRead(buttonPin);

  leftButtonState = false;
  rightButtonState = false;

  // Gets the raw data for which buttons are pressed
  if (input <= in1)
  {
    leftButtonState = true;
    rightButtonState = true;
  }
  else if (input <= in2)
  {
    leftButtonState = true;
  }
  else if (input <= in3)
  {
    rightButtonState = true;
  }

  // If the button was just pressed then set the filter to true
  if (leftButtonState && !leftPrevButtonState)
  {
    filteredLeftButton = true;
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
  return toReturn;
}

// Returns if the left button is pressed
boolean isLeftButtonUnfil()
{
  return leftButtonState;
}

// Returns if the right button is pressed
boolean isRightButtonUnfil()
{
  return rightButtonState;
}

boolean leftButtonState = false; // The left button state
boolean leftPrevButtonState = true; // The left button's previous state (true to prevent program from thinking button was pushed at beginning)

boolean rightButtonState = false; // The right button state
boolean rightPrevButtonState = true; // The right button's previous state (true to prevent program from thinking button was pushed at beginning)

// Updates the input variables based on pin state
void updateInput()
{
  int inputLeft = analogRead(buttonPinLeft);
  int inputRight = analogRead(buttonPinRight);

  leftButtonState = (inputLeft > 511);
  rightButtonState = (inputRight > 511);

  // Sets the previous button states for the next time input() is called
  leftPrevButtonState = leftButtonState;
  rightPrevButtonState = rightButtonState;
}

// Returns if the left button is pressed (one time use to prevent button spamming)
boolean isLeftButton()
{
  return (leftButtonState && !leftPrevButtonState); // If the button was just pressed then set the filter to true
}

// Returns if the right button is pressed (one time use to prevent button spamming)
boolean isRightButton()
{
  return (rightButtonState && !rightPrevButtonState); // If the button was just pressed then set the filter to true
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

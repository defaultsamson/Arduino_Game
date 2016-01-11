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

#define buttonPinLeft 18 // The pin assigned to the button input
#define buttonPinRight 17 // The pin assigned to the button input
#define piezoPin1 19 // The pin assigned to the first piezo buzzer
#define piezoPin2 16 // The pin assigned to the second piezo buzzer

byte pixelPin[] = {12, 3, 4, 8,
                   13, 2, 5, 9,
                   14, 1, 6, 10,
                   15, 0, 7, 11
                  }; // The pins for each of the piexels in their corrosponding order

#define renderFrequency 30 // Frequency of rendering in Hz
long lastRender = 0; // The time of the previous render in milliseconds

byte tickFrequency = 30; // Frequency of each tick in Hz
long lastTick = 0; // The time of the previous tick in milliseconds

int tickFrequencyChangeInterval = 0; // The amount of milliseconds to wait before increasing the tick frequency
long lastTickFrequencyChange = 0; // The last time the tick rate was changed
byte tickFrequencyMax = 30; // The maximum tick frequency

long currentTime = 0; // The current time in milliseconds

// The setup script
void setup()
{
  Serial.begin(9600);

  // Sets up the pins
  pinMode(buttonPinLeft, INPUT);
  pinMode(buttonPinRight, INPUT);
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
}

// The game loop
void loop()
{
  currentTime = millis();

  // Updates music constantly for better responsiveness
  music(currentTime);
  updateInput();

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

  // Every specified ticks, make the tick interval faster if it is above the minimum interval rate
  if (tickFrequencyChangeInterval > 0 && (lastTickFrequencyChange + (1000 / tickFrequencyChangeInterval)) < currentTime && tickFrequency < tickFrequencyMax)
  {
    tickFrequency++;
    lastTickFrequencyChange = currentTime;
  }
}

byte currentSong = 1; // The current song being played

#define songArrayLengths 128

int mainTone[songArrayLengths];
byte mainDuration[songArrayLengths];

int bassTone[songArrayLengths];
byte bassDuration[songArrayLengths];

byte bpm = 150;

int* songTones[] = {mainTone, bassTone};
byte* toneDurations[] = {mainDuration, bassDuration};
int trackLengths[2];

#define playNoteIndexLength 2
int playNoteIndex[] = {0, 0};
int lastTime[] = {0, 0};

boolean initMusic = true;

void playSong(byte songIndex)
{
  if (initMusic) // Initializes all song arrays
  {
    for (int i = 0; i < songArrayLengths; i++) mainTone[i] = 0;
    for (int i = 0; i < songArrayLengths; i++) mainDuration[i] = 0;
    for (int i = 0; i < songArrayLengths; i++) bassTone[i] = 0;
    for (int i = 0; i < songArrayLengths; i++) bassDuration[i] = 0;
    
    for (int i = 0; i < playNoteIndexLength; i++) trackLengths[i] = 0;

    initMusic = false;
  }
  
  playNoteIndex[0] = 0;
  playNoteIndex[1] = 0;
  lastTime[0] = 0;
  lastTime[1] = 0;

  
  if (songIndex = 1)
  {
    int mainTetris[] = {NOTE_E6, NOTE_B5, NOTE_C6, NOTE_D6, NOTE_E6, NOTE_D6, NOTE_C6, NOTE_B5,
                  NOTE_A5, NOTE_A5, 0, NOTE_A5, NOTE_C6, NOTE_E6, NOTE_D6, NOTE_C6,
                  NOTE_B5, NOTE_B5, NOTE_C6, NOTE_D6, NOTE_E6,
                  NOTE_C6, NOTE_A5, NOTE_A5, 0,
                  0, NOTE_D6, NOTE_F6, NOTE_A6, NOTE_G6, NOTE_F6,
                  NOTE_E6, NOTE_E6, NOTE_C6, NOTE_E6, NOTE_D6, NOTE_C6,
                  NOTE_B5, NOTE_B5, NOTE_C6, NOTE_D6, NOTE_E6,
                  NOTE_C6, NOTE_A5, NOTE_A5,
                  
                  NOTE_E6, NOTE_C6, 
                  NOTE_D6, NOTE_B5,
                  NOTE_C6, NOTE_A5,
                  NOTE_GS5, NOTE_B5, 0,
                  NOTE_E6, NOTE_C6, 
                  NOTE_D6, NOTE_B5,
                  NOTE_C6, NOTE_E6, NOTE_A6,
                  NOTE_GS6
                  };
    for (int i = 0; i < sizeof(mainTetris); i++) mainTone[i] = mainTetris[i];

    byte tetrisDuration[] = {4, 8, 8, 8, 16, 16, 8, 8,
                       8, 16, 16, 8, 8, 4, 8, 8,
                       4, 8, 8, 4, 4,
                       4, 4, 4, 4,
                       8, 4, 8, 4, 8, 8,
                       4, 8, 8, 4, 8, 8,
                       4, 8, 8, 4, 4,
                       4, 4, 2,

                       2, 2,
                       2, 2,
                       2, 2,
                       2, 4, 4,
                       2, 2,
                       2, 2,
                       4, 4, 2,
                       1
                       };
    for (int i = 0; i < sizeof(tetrisDuration); i++) mainDuration[i] = tetrisDuration[i];
    
    for (int iy = 0; iy < 16; iy++)
    {
      // Sets up duration based on bar
      for (int ix = 0; ix < 8; ix++)
      {
        bassDuration[(iy * 8) + ix] = 8;
      }

      int tone1Value = 0;
      int tone2Value = 0;

      boolean doRepeats = true;

      switch (iy) // Sets up the tones based on the bar
      {
        case 0:
          tone1Value = NOTE_E4;
          tone2Value = NOTE_E5;
          break;
        case 1:
        case 7:
        case 8:
        case 10:
        case 12:
        case 14:
          tone1Value = NOTE_A3;
          tone2Value = NOTE_A4;
          break;
        case 2:
        case 6:
        case 9:
        case 11:
        case 13:
        case 15:
          tone1Value = NOTE_GS3;
          tone2Value = NOTE_GS4;
          break;
        case 3:
          bassTone[(iy * 8)] = NOTE_A3;
          bassTone[(iy * 8) + 1] = NOTE_A4;
          bassTone[(iy * 8) + 2] = NOTE_A3;
          bassTone[(iy * 8) + 3] = NOTE_A4;
          bassTone[(iy * 8) + 4] = NOTE_A3;
          bassTone[(iy * 8) + 5] = NOTE_A4;
          bassTone[(iy * 8) + 6] = NOTE_B4;
          bassTone[(iy * 8) + 7] = NOTE_C5;
          doRepeats = false;
          break;
        case 4:
          tone1Value = NOTE_D4;
          tone2Value = NOTE_D5;
          break;
        case 5:
          tone1Value = NOTE_C4;
          tone2Value = NOTE_C5;
          break;
      }

      if (doRepeats)
      {
        for (int ix = 0; ix < 4; ix++)
        {
          bassTone[(iy * 8) + (ix * 2)] = tone1Value;
          bassTone[(iy * 8) + (ix * 2) + 1] = tone2Value;
        }
      }
    }
    
    trackLengths[0] = 62; 
    trackLengths[1] = 128;
    bpm = 150;

    currentSong = 1;
    /*
    NOTE_E4, NOTE_E5, NOTE_E4, NOTE_E5, NOTE_E4, NOTE_E5, NOTE_E4, NOTE_E5,
    NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4,
    NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4,
    NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_B4, NOTE_C5,
    NOTE_D4, NOTE_D5, NOTE_D4, NOTE_D5, NOTE_D4, NOTE_D5, NOTE_D4, NOTE_D5,
    NOTE_C4, NOTE_C5, NOTE_C4, NOTE_C5, NOTE_C4, NOTE_C5, NOTE_C4, NOTE_C5,
    NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4,
    NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4,
    x2
    
    NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4,
    NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4,
    NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4,
    NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4,
    NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4,
    NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4,
    NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4,
    NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4,}
    */
    
    /*
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8
    */
  }
}
else if (songIndex = 2) {

    int mainDummy[] = {
      NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_CS5, 0, NOTE_D5, NOTE_FS5,
      NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_CS5, 0, NOTE_F5, NOTE_A5,
      NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_CS5, 0, NOTE_D5, NOTE_FS5,
      NOTE_AS4, NOTE_C5, NOTE_CS5, 0, NOTE_D5, NOTE_FS5,  NOTE_AS4, NOTE_C5, NOTE_CS5, 0, NOTE_D5, NOTE_FS5,
      NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_D5, NOTE_FS5, NOTE_G5, 0, 0,
      NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_G4, NOTE_CS5, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_CS5, NOTE_F4, NOTE_G4,
      NOTE_AS4, NOTE_G4, NOTE_F4, NOTE_G5, NOTE_F5, NOTE_CS5, NOTE_C5, NOTE_AS4, NOTE_G4, NOTE_A4, NOTE_AS4, NOTE_DS5,
      NOTE_D5, NOTE_G4, NOTE_G5, NOTE G4, NOTE_FS5, NOTE_DS5, NOTE_D5, NOTE_ DS5, NOTE_D5, NOTE_DS5,
      NOTE_D5, NOTE_AS4, NOTE_G4, NOTE_D4, NOTE_AS4, NOTE_G4, NOTE_A5, NOTE_DS5, NOTE_D5, NOTE_DS5,
      NOTE_AS4, NOTE_G4, NOTE_A5, NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_D5, NOTE_G5, NOTE_C5, NOTE_G4,
      NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_CS5, NOTE_C5, NOTE_AS4, NOTE_G4, NOTE_D4,
      NOTE_F4, NOTE_FS4, NOTE_G4,

    };
    for (int i = 0; i < sizeof(mainDummy); i++) mainTone[i] = mainDummy[i];

    byte dummyDuration[] = {
      4, 4, 4, 4, 4, 8, 8, 8, 8, 4,
      4, 4, 4, 4, 4, 8, 8, 8, 8, 4,
      4, 4, 4, 4, 4, 8, 8, 8, 8, 4,
      4, 8, 8, 8, 8, 4, 4, 8, 8, 8, 8, 4,
      4, 4, 4, 4, 8, 4, 8, 2, 4, 2, 3,
      3, 6, 16, 3, 8, 8, 8, 8, 8, 8, 8,
      8, 8, 8, 4, 8, 12, 12, 8, 2, 2, 2, 2,
      4, 4, 4, 4, 8, 4, 4, 8, 8, 8,
      4, 4, 4, 4, 4, 8, 4, 8, 8, 8,
      4, 8, 4, 8, 8, 8, 4, 4, 4, 4
      8, 4, 3, 6, 16, 8, 8, 4, 4, 4
      8, 4, 1,

    };
    for (int i = 0; i < sizeof(dummyDuration); i++) mainDuration[i] = dummyDuration[i];


int bassDummy[] = {
      0, 0, 0, 0, 0, 0, 0, 0,
      NOTE_G4, NOTE_G4, NOTE_F4, NOTE_ES4, NOTE_DS4, NOTE_D4, NOTE_AS3, NOTE_G3, NOTE_DS3, 
      NOTE_D4, NOTE_AS3, NOTE_G3, NOTE_DS3, NOTE_D4, NOTE_AS3, NOTE_G3, NOTE_DS3,
      NOTE_C4, NOTE_C4, NOTE_AS3, NOTE_C4, NOTE_CS4, 0, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_ES4, NOTE_DS4
      NOTE_G4, NOTE_G4, NOTE_F4, NOTE_ES4, NOTE_DS4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_F4,
     NOTE_G3, NOTE_A3, NOTE_AS3, NOTE_G3, NOTE_G3, NOTE_D4, NOTE_G4, NOTE_D4,
      NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_D4, NOTE_G4, NOTE_AS4, NOTE_C4, NOTE_G4,
      NOTE_AS4, NOTE_C5, NOTE_CS5, 0, NOTE_D5, NOTE_FS5, NOTE_AS4, NOTE_C5, NOTE_CS5, 0, NOTE_D5, NOTE_FS5,  
      NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_G4, 
      NOTE_AS4, NOTE_C5, NOTE_CS5, 0, NOTE_D5, NOTE_FS5, NOTE_AS4, NOTE_C5, NOTE_CS5, 0, NOTE_D5, NOTE_FS5,  
      NOTE_FS5, NOTE_D5, NOTE_G5,
    };
    for (int i = 0; i < sizeof(mainDummy); i++) mainTone[i] = mainDummy[i];

    byte bassDummyDuration[] = {
      1, 1, 1, 1, 1, 1, 1, 1, 
      8, 8, 4, 4, 4, 4, 4, 4, 4
      4, 4, 4, 4, 4, 4, 4, 4,
      8, 8, 4, 4, 4, 1, 8, 8, 4, 4, 4,
      8, 8, 4, 4, 4, 4, 4, 4, 4,
      2, 2, 2, 2, 4, 4, 4, 4, 
      8, 4, 4, 6, 4, 4, 4, 4,
      4, 8, 8, 8, 8, 4, 4, 8, 8, 8, 8, 4,
      4, 4, 4, 4,
      4, 8, 8, 8, 8, 4, 4, 8, 8, 8, 8, 4,
      4, 4, 1,
      
      
      
      
       
      
     

    };
    for (int i = 0; i < sizeof(dummyDuration); i++) mainDuration[i] = dummyDuration[i];

  }

void stopSong()
{
  currentSong = 0;
}

// Plays the current song if there is one
void music(long currentTime)
{
  if (currentSong > 0)
  {
    for (int i = 0; i < playNoteIndexLength; i++) // sizeof(playNoteIndex) returns 4 for some reason, so manually replace it with 2
    {
      if (playNoteIndex[i] < trackLengths[i])
      {
        int lastDuration = 0;

        if (playNoteIndex[i] > 0) // If the first note has been played, play the next note after the original note is finished. Else play immediately
        {
          int noteDuration = toneDurations[i][playNoteIndex[i] - 1];
          lastDuration = 60000 / (bpm / 4) / noteDuration;
        }

        // If the last note is done playing
        if (currentTime > (lastTime[i] + lastDuration))
        {
          lastTime[i] = currentTime;
          // Play the next note in the current song
          int duration = 60000 / (bpm / 4) / toneDurations[i][playNoteIndex[i]];
          int noteTone = songTones[i][playNoteIndex[i]];

          // Plays the note on the tone generator
          tonePlayer[i].stop();
          tonePlayer[i].play(noteTone, duration);

          // Increases the note index being played
          playNoteIndex[i]++;
        }
      }
    }
  }
}

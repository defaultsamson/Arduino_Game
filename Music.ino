byte currentSong = 0; // The current song being played

int tetrisMainTone[] = {NOTE_E6, NOTE_B5, NOTE_C6, NOTE_D6, NOTE_E6, NOTE_D6, NOTE_C6, NOTE_B5,
                        NOTE_A5, NOTE_A5, NOTE_C6, NOTE_E6, NOTE_D6, NOTE_C6,
                        NOTE_B5, NOTE_B5, NOTE_C6, NOTE_D6, NOTE_E6,
                        NOTE_C6, NOTE_A5, NOTE_A5, 0,
                        0, NOTE_D6, NOTE_F6, NOTE_A6, NOTE_G6, NOTE_F6,
                        NOTE_E6, NOTE_E6, NOTE_C6, NOTE_E6, NOTE_D6, NOTE_C6,
                        NOTE_B5, NOTE_B5, NOTE_C6, NOTE_D6, NOTE_E6,
                        NOTE_C6, NOTE_A5, NOTE_A5,
                        NOTE_E6, NOTE_C6, 
                        NOTE_D6, NOTE_B5,
                        NOTE_C6, NOTE_A5,
                        NOTE_GS5, NOTE_B5,
                        NOTE_E6, NOTE_C6, 
                        NOTE_D6, NOTE_B5,
                        NOTE_C6, NOTE_E6, NOTE_A6,
                        NOTE_GS6
                       };
byte tetrisMainDuration[] = {4, 8, 8, 8, 16, 16, 8, 8,
                             4, 8, 8, 4, 8, 8,
                             4, 8, 8, 4, 4,
                             4, 4, 4, 4,
                             8, 4, 8, 4, 8, 8,
                             4, 8, 8, 4, 8, 8,
                             4, 8, 8, 4, 4,
                             4, 4, 2,
                             2, 2,
                             2, 2,
                             2, 2,
                             2, 2,
                             2, 2,
                             2, 2,
                             4, 4, 2,
                             1
                            };
int tetrisBassTone[] = {NOTE_E4, NOTE_E5, NOTE_E4, NOTE_E5, NOTE_E4, NOTE_E5, NOTE_E4, NOTE_E5,
                        NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4,
                        NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4,
                        NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_B4, NOTE_C5,
                        NOTE_D4, NOTE_D5, NOTE_D4, NOTE_D5, NOTE_D4, NOTE_D5, NOTE_D4, NOTE_D5,
                        NOTE_C4, NOTE_C5, NOTE_C4, NOTE_C5, NOTE_C4, NOTE_C5, NOTE_C4, NOTE_C5,
                        NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4,
                        NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4,
                        NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4,
                        NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4,
                        NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4,
                        NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4,
                        NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4,
                        NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4,
                        NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4,
                        NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4, NOTE_GS3, NOTE_GS4
                       };
byte tetrisBassDuration[] = {8, 8, 8, 8, 8, 8, 8, 8,
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
                            };
byte bpm1 = 135;

int* songTones[] = {tetrisMainTone, tetrisBassTone};
byte* toneDurations[] = {tetrisMainDuration, tetrisBassDuration};
int trackLengths[] = {sizeof(tetrisMainTone) / 2, sizeof(tetrisBassTone) / 2};
byte songBpm[] = {bpm1};

#define playNoteIndexLength 2
int playNoteIndex[] = {0, 0};
int lastTime[] = {0, 0};

// Plays the current song if there is one
void music(long currentTime)
{
  if (currentSong >= 0)
  {
    for (int i = 0; i < playNoteIndexLength; i++) // sizeof(playNoteIndex) returns 4 for some reason, so manually replace it with 2
    {
      if (playNoteIndex[i] < trackLengths[currentSong + i])
      {
        int lastDuration = 0;

        if (playNoteIndex[i] > 0) // If the first note has been played, play the next note after the original note is finished. Else play immediately
        {
          int noteDuration = toneDurations[currentSong + i][playNoteIndex[i] - 1];
          lastDuration = 60000 / (songBpm[currentSong] / 4) / noteDuration;
        }

        // If the last note is done playing
        if (currentTime > (lastTime[i] + lastDuration))
        {
          lastTime[i] = currentTime;
          // Play the next note in the current song
          int duration = 60000 / (songBpm[currentSong] / 4) / toneDurations[currentSong][playNoteIndex[i]];
          int noteTone = songTones[currentSong + i][playNoteIndex[i]];

          // Plays the note on the tone generator
          tonePlayer[i].play(noteTone, duration);

          // Increases the note index being played
          playNoteIndex[i]++;
        }
      }
    }
  }
}

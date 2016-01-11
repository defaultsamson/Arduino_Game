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

void playSong(byte songIndex)
{
  stopSong();

  if (songIndex == 1)
  {
    mainTone[0] = NOTE_E6;
    mainTone[1] = NOTE_B5;
    mainTone[2] = NOTE_C6;
    mainTone[3] = NOTE_D6;
    mainTone[4] = NOTE_E6;
    mainTone[5] = NOTE_D6;
    mainTone[6] = NOTE_C6;
    mainTone[7] = NOTE_B5;
    mainTone[8] = NOTE_A5;
    mainTone[9] = NOTE_A5;
    mainTone[10] = 0;
    mainTone[11] = NOTE_A5;
    mainTone[12] = NOTE_C6;
    mainTone[13] = NOTE_E6;
    mainTone[14] = NOTE_D6;
    mainTone[15] = NOTE_C6;
    mainTone[16] = NOTE_B5;
    mainTone[17] = NOTE_B5;
    mainTone[18] = NOTE_C6;
    mainTone[19] = NOTE_D6;
    mainTone[20] = NOTE_E6;
    mainTone[21] = NOTE_C6;
    mainTone[22] = NOTE_A5;
    mainTone[23] = NOTE_A5;
    mainTone[24] = 0;
    mainTone[25] = 0;
    mainTone[26] = NOTE_D6;
    mainTone[27] = NOTE_F6;
    mainTone[28] = NOTE_A6;
    mainTone[29] = NOTE_G6;
    mainTone[30] = NOTE_F6;
    mainTone[31] = NOTE_E6;
    mainTone[32] = NOTE_E6;
    mainTone[33] = NOTE_C6;
    mainTone[34] = NOTE_E6;
    mainTone[35] = NOTE_D6;
    mainTone[36] = NOTE_C6;
    mainTone[37] = NOTE_B5;
    mainTone[38] = NOTE_B5;
    mainTone[39] = NOTE_C6;
    mainTone[40] = NOTE_D6;
    mainTone[41] = NOTE_E6;
    mainTone[42] = NOTE_C6;
    mainTone[43] = NOTE_A5;
    mainTone[44] = NOTE_A5;
    mainTone[45] = NOTE_E6;
    mainTone[46] = NOTE_C6;
    mainTone[47] = NOTE_D6;
    mainTone[48] = NOTE_B5;
    mainTone[49] = NOTE_C6;
    mainTone[50] = NOTE_A5;
    mainTone[51] = NOTE_GS5;
    mainTone[52] = NOTE_B5;
    mainTone[53] = 0;
    mainTone[54] = NOTE_E6;
    mainTone[55] = NOTE_C6;
    mainTone[56] = NOTE_D6;
    mainTone[57] = NOTE_B5;
    mainTone[58] = NOTE_C6;
    mainTone[59] = NOTE_E6;
    mainTone[60] = NOTE_A6;
    mainTone[61] = NOTE_GS6;

    /*
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
    */

    mainDuration[0] = 4;
    mainDuration[1] = 8;
    mainDuration[2] = 8;
    mainDuration[3] = 8;
    mainDuration[4] = 16;
    mainDuration[5] = 16;
    mainDuration[6] = 8;
    mainDuration[7] = 8;
    mainDuration[8] = 8;
    mainDuration[9] = 16;
    mainDuration[10] = 16;
    mainDuration[11] = 8;
    mainDuration[12] = 8;
    mainDuration[13] = 4;
    mainDuration[14] = 8;
    mainDuration[15] = 8;
    mainDuration[16] = 4;
    mainDuration[17] = 8;
    mainDuration[18] = 8;
    mainDuration[19] = 4;
    mainDuration[20] = 4;
    mainDuration[21] = 4;
    mainDuration[22] = 4;
    mainDuration[23] = 4;
    mainDuration[24] = 4;
    mainDuration[25] = 8;
    mainDuration[26] = 4;
    mainDuration[27] = 8;
    mainDuration[28] = 4;
    mainDuration[29] = 8;
    mainDuration[30] = 8;
    mainDuration[31] = 4;
    mainDuration[32] = 8;
    mainDuration[33] = 8;
    mainDuration[34] = 4;
    mainDuration[35] = 8;
    mainDuration[36] = 8;
    mainDuration[37] = 4;
    mainDuration[38] = 8;
    mainDuration[39] = 8;
    mainDuration[40] = 4;
    mainDuration[41] = 4;
    mainDuration[42] = 4;
    mainDuration[43] = 4;
    mainDuration[44] = 2;
    mainDuration[45] = 2;
    mainDuration[46] = 2;
    mainDuration[47] = 2;
    mainDuration[48] = 2;
    mainDuration[49] = 2;
    mainDuration[50] = 2;
    mainDuration[51] = 2;
    mainDuration[52] = 4;
    mainDuration[53] = 4;
    mainDuration[54] = 2;
    mainDuration[55] = 2;
    mainDuration[56] = 2;
    mainDuration[57] = 2;
    mainDuration[58] = 4;
    mainDuration[59] = 4;
    mainDuration[60] = 2;
    mainDuration[61] = 1;

    /*
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
    */

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
  else if (songIndex == 2)
  {
    mainTone[0] = NOTE_G4;
    mainTone[1] = NOTE_AS4;
    mainTone[2] = NOTE_C5;
    mainTone[3] = NOTE_G4;
    mainTone[4] = NOTE_AS4;
    mainTone[5] = NOTE_C5;
    mainTone[6] = NOTE_CS5;
    mainTone[7] = 0;
    mainTone[8] = NOTE_D5;
    mainTone[9] = NOTE_FS5;
    mainTone[10] = NOTE_G4;
    mainTone[11] = NOTE_AS4;
    mainTone[12] = NOTE_C5;
    mainTone[13] = NOTE_G4;
    mainTone[14] = NOTE_AS4;
    mainTone[15] = NOTE_C5;
    mainTone[16] = NOTE_CS5;
    mainTone[17] = 0;
    mainTone[18] = NOTE_F5;
    mainTone[19] = NOTE_A5;
    mainTone[20] = NOTE_G4;
    mainTone[21] = NOTE_AS4;
    mainTone[22] = NOTE_C5;
    mainTone[23] = NOTE_G4;
    mainTone[24] = NOTE_AS4;
    mainTone[25] = NOTE_C5;
    mainTone[26] = NOTE_CS5;
    mainTone[27] = 0;
    mainTone[28] = NOTE_D5;
    mainTone[29] = NOTE_FS5;
    mainTone[30] = NOTE_AS4;
    mainTone[31] = NOTE_C5;
    mainTone[32] = NOTE_CS5;
    mainTone[33] = 0;
    mainTone[34] = NOTE_D5;
    mainTone[35] = NOTE_FS5;
    mainTone[36] = NOTE_AS4;
    mainTone[37] = NOTE_C5;
    mainTone[38] = NOTE_CS5;
    mainTone[39] = 0;
    mainTone[40] = NOTE_D5;
    mainTone[41] = NOTE_FS5;
    mainTone[42] = NOTE_G4;
    mainTone[43] = NOTE_AS4;
    mainTone[44] = NOTE_C5;
    mainTone[45] = NOTE_DS5;
    mainTone[46] = NOTE_D5;
    mainTone[47] = NOTE_DS5;
    mainTone[48] = NOTE_D5;
    mainTone[49] = NOTE_FS5;
    mainTone[50] = NOTE_G5;
    mainTone[51] = 0;
    mainTone[52] = 0;
    mainTone[53] = NOTE_D5;
    mainTone[54] = NOTE_C5;
    mainTone[55] = NOTE_AS4;
    mainTone[56] = NOTE_G4;
    mainTone[57] = NOTE_CS5;
    mainTone[58] = NOTE_C5;
    mainTone[59] = NOTE_AS4;
    mainTone[60] = NOTE_C5;
    mainTone[61] = NOTE_CS5;
    mainTone[62] = NOTE_F4;
    mainTone[63] = NOTE_G4;
    mainTone[64] = NOTE_AS4;
    mainTone[65] = NOTE_G4;
    mainTone[66] = NOTE_F4;
    mainTone[67] = NOTE_G5;
    mainTone[68] = NOTE_F5;
    mainTone[69] = NOTE_CS5;
    mainTone[70] = NOTE_C5;
    mainTone[71] = NOTE_AS4;
    mainTone[72] = NOTE_G4;
    mainTone[73] = NOTE_A4;
    mainTone[74] = NOTE_AS4;
    mainTone[75] = NOTE_DS5;
    mainTone[76] = NOTE_D5;
    mainTone[77] = NOTE_G4;
    mainTone[78] = NOTE_G5;
    mainTone[79] = NOTE_G4;
    mainTone[80] = NOTE_FS5;
    mainTone[81] = NOTE_DS5;
    mainTone[82] = NOTE_D5;
    mainTone[83] = NOTE_DS5;
    mainTone[84] = NOTE_D5;
    mainTone[85] = NOTE_DS5;
    mainTone[86] = NOTE_D5;
    mainTone[87] = NOTE_AS4;
    mainTone[88] = NOTE_G4;
    mainTone[89] = NOTE_D4;
    mainTone[90] = NOTE_AS4;
    mainTone[91] = NOTE_G4;
    mainTone[92] = NOTE_A5;
    mainTone[93] = NOTE_DS5;
    mainTone[94] = NOTE_D5;
    mainTone[95] = NOTE_DS5;
    mainTone[96] = NOTE_AS4;
    mainTone[97] = NOTE_G4;
    mainTone[98] = NOTE_A5;
    mainTone[99] = NOTE_DS5;
    mainTone[100] = NOTE_D5;
    mainTone[101] = NOTE_DS5;
    mainTone[102] = NOTE_D5;
    mainTone[103] = NOTE_G5;
    mainTone[104] = NOTE_C5;
    mainTone[105] = NOTE_G4;
    mainTone[106] = NOTE_C5;
    mainTone[107] = NOTE_AS4;
    mainTone[108] = NOTE_C5;
    mainTone[109] = NOTE_AS4;
    mainTone[110] = NOTE_C5;
    mainTone[111] = NOTE_CS5;
    mainTone[112] = NOTE_C5;
    mainTone[113] = NOTE_AS4;
    mainTone[114] = NOTE_G4;
    mainTone[115] = NOTE_D4;
    mainTone[116] = NOTE_F4;
    mainTone[117] = NOTE_FS4;
    mainTone[118] = NOTE_G4;

    trackLengths[0] = 119;

    /* int mainDummy[] = {
      NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_CS5, 0, NOTE_D5, NOTE_FS5,
      NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_CS5, 0, NOTE_F5, NOTE_A5,
      NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_CS5, 0, NOTE_D5, NOTE_FS5,
      NOTE_AS4, NOTE_C5, NOTE_CS5, 0, NOTE_D5, NOTE_FS5,  NOTE_AS4, NOTE_C5, NOTE_CS5, 0, NOTE_D5, NOTE_FS5,
      NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_D5, NOTE_FS5, NOTE_G5, 0, 0,
      NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_G4, NOTE_CS5, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_CS5, NOTE_F4, NOTE_G4,
      NOTE_AS4, NOTE_G4, NOTE_F4, NOTE_G5, NOTE_F5, NOTE_CS5, NOTE_C5, NOTE_AS4, NOTE_G4, NOTE_A4, NOTE_AS4, NOTE_DS5,
      NOTE_D5, NOTE_G4, NOTE_G5, NOTE_G4, NOTE_FS5, NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_D5, NOTE_DS5,
      NOTE_D5, NOTE_AS4, NOTE_G4, NOTE_D4, NOTE_AS4, NOTE_G4, NOTE_A5, NOTE_DS5, NOTE_D5, NOTE_DS5,
      NOTE_AS4, NOTE_G4, NOTE_A5, NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_D5, NOTE_G5, NOTE_C5, NOTE_G4,
      NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_CS5, NOTE_C5, NOTE_AS4, NOTE_G4, NOTE_D4,
      NOTE_F4, NOTE_FS4, NOTE_G4
      };
    */

    mainDuration[0] = 4;
    mainDuration[1] = 4;
    mainDuration[2] = 4;
    mainDuration[3] = 4;
    mainDuration[4] = 4;
    mainDuration[5] = 8;
    mainDuration[6] = 8;
    mainDuration[7] = 8;
    mainDuration[8] = 8;
    mainDuration[9] = 4;
    mainDuration[10] = 4;
    mainDuration[11] = 4;
    mainDuration[12] = 4;
    mainDuration[13] = 4;
    mainDuration[14] = 4;
    mainDuration[15] = 8;
    mainDuration[16] = 8;
    mainDuration[17] = 8;
    mainDuration[18] = 8;
    mainDuration[19] = 4;
    mainDuration[20] = 4;
    mainDuration[21] = 4;
    mainDuration[22] = 4;
    mainDuration[23] = 4;
    mainDuration[24] = 4;
    mainDuration[25] = 8;
    mainDuration[26] = 8;
    mainDuration[27] = 8;
    mainDuration[28] = 8;
    mainDuration[29] = 4;
    mainDuration[30] = 4;
    mainDuration[31] = 8;
    mainDuration[32] = 8;
    mainDuration[33] = 8;
    mainDuration[34] = 8;
    mainDuration[35] = 4;
    mainDuration[36] = 4;
    mainDuration[37] = 8;
    mainDuration[38] = 8;
    mainDuration[39] = 8;
    mainDuration[40] = 8;
    mainDuration[41] = 4;
    mainDuration[42] = 4;
    mainDuration[43] = 4;
    mainDuration[44] = 4;
    mainDuration[45] = 4;
    mainDuration[46] = 8;
    mainDuration[47] = 4;
    mainDuration[48] = 8;
    mainDuration[49] = 2;
    mainDuration[50] = 4;
    mainDuration[51] = 2;
    mainDuration[52] = 3;
    mainDuration[53] = 3;
    mainDuration[54] = 6;
    mainDuration[55] = 16;
    mainDuration[56] = 3;
    mainDuration[57] = 8;
    mainDuration[58] = 8;
    mainDuration[59] = 8;
    mainDuration[60] = 8;
    mainDuration[61] = 8;
    mainDuration[62] = 8;
    mainDuration[63] = 8;
    mainDuration[64] = 8;
    mainDuration[65] = 8;
    mainDuration[66] = 8;
    mainDuration[67] = 4;
    mainDuration[68] = 8;
    mainDuration[69] = 12;
    mainDuration[70] = 12;
    mainDuration[71] = 8;
    mainDuration[72] = 2;
    mainDuration[73] = 2;
    mainDuration[74] = 2;
    mainDuration[75] = 2;
    mainDuration[76] = 4;
    mainDuration[77] = 4;
    mainDuration[78] = 4;
    mainDuration[79] = 4;
    mainDuration[80] = 8;
    mainDuration[81] = 4;
    mainDuration[82] = 4;
    mainDuration[83] = 8;
    mainDuration[84] = 8;
    mainDuration[85] = 8;
    mainDuration[86] = 4;
    mainDuration[87] = 4;
    mainDuration[88] = 4;
    mainDuration[89] = 4;
    mainDuration[90] = 4;
    mainDuration[91] = 8;
    mainDuration[92] = 4;
    mainDuration[93] = 8;
    mainDuration[94] = 8;
    mainDuration[95] = 8;
    mainDuration[96] = 4;
    mainDuration[97] = 8;
    mainDuration[98] = 4;
    mainDuration[99] = 8;
    mainDuration[100] = 8;
    mainDuration[101] = 8;
    mainDuration[102] = 4;
    mainDuration[103] = 4;
    mainDuration[104] = 4;
    mainDuration[105] = 4;
    mainDuration[106] = 8;
    mainDuration[107] = 4;
    mainDuration[108] = 3;
    mainDuration[109] = 6;
    mainDuration[110] = 16;
    mainDuration[111] = 8;
    mainDuration[112] = 8;
    mainDuration[113] = 4;
    mainDuration[114] = 4;
    mainDuration[115] = 4;
    mainDuration[116] = 8;
    mainDuration[117] = 4;
    mainDuration[118] = 1;

    /*
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
      4, 8, 4, 8, 8, 8, 4, 4, 4, 4,
      8, 4, 3, 6, 16, 8, 8, 4, 4, 4,
      8, 4, 1
      };
    */

    bassTone[0] = 0;
    bassTone[1] = 0;
    bassTone[2] = 0;
    bassTone[3] = 0;
    bassTone[4] = NOTE_G4;
    bassTone[5] = NOTE_G4;
    bassTone[6] = NOTE_F4;
    bassTone[7] = NOTE_E4;
    bassTone[8] = NOTE_DS4;
    bassTone[9] = NOTE_D4;
    bassTone[10] = NOTE_AS3;
    bassTone[11] = NOTE_G3;
    bassTone[12] = NOTE_DS3;
    bassTone[13] = NOTE_D4;
    bassTone[14] = NOTE_AS3;
    bassTone[15] = NOTE_G3;
    bassTone[16] = NOTE_DS3;
    bassTone[17] = NOTE_D4;
    bassTone[18] = NOTE_AS3;
    bassTone[19] = NOTE_G3;
    bassTone[20] = NOTE_DS3;
    bassTone[21] = NOTE_C4;
    bassTone[22] = NOTE_C4;
    bassTone[23] = NOTE_AS3;
    bassTone[24] = NOTE_C4;
    bassTone[25] = NOTE_CS4;
    bassTone[26] = 0;
    bassTone[27] = NOTE_G4;
    bassTone[28] = NOTE_G4;
    bassTone[29] = NOTE_F4;
    bassTone[30] = NOTE_E4;
    bassTone[31] = NOTE_DS4;
    bassTone[32] = NOTE_G4;
    bassTone[33] = NOTE_G4;
    bassTone[34] = NOTE_F4;
    bassTone[35] = NOTE_E4;
    bassTone[36] = NOTE_DS4;
    bassTone[37] = NOTE_D4;
    bassTone[38] = NOTE_G4;
    bassTone[39] = NOTE_FS4;
    bassTone[40] = NOTE_F4;
    bassTone[41] = NOTE_G3;
    bassTone[42] = NOTE_A3;
    bassTone[43] = NOTE_AS3;
    bassTone[44] = NOTE_G3;
    bassTone[45] = NOTE_G3;
    bassTone[46] = NOTE_D4;
    bassTone[47] = NOTE_G4;
    bassTone[48] = NOTE_D4;
    bassTone[49] = NOTE_G4;
    bassTone[50] = NOTE_A4;
    bassTone[51] = NOTE_FS4;
    bassTone[52] = NOTE_D4;
    bassTone[53] = NOTE_G4;
    bassTone[54] = NOTE_AS4;
    bassTone[55] = NOTE_C4;
    bassTone[56] = NOTE_G4;
    bassTone[57] = NOTE_AS4;
    bassTone[58] = NOTE_C5;
    bassTone[59] = NOTE_CS5;
    bassTone[60] = 0;
    bassTone[61] = NOTE_D5;
    bassTone[62] = NOTE_FS5;
    bassTone[63] = NOTE_AS4;
    bassTone[64] = NOTE_C5;
    bassTone[65] = NOTE_CS5;
    bassTone[66] = 0;
    bassTone[67] = NOTE_D5;
    bassTone[68] = NOTE_FS5;
    bassTone[69] = NOTE_G4;
    bassTone[70] = NOTE_AS4;
    bassTone[71] = NOTE_C5;
    bassTone[72] = NOTE_G4;
    bassTone[73] = NOTE_AS4;
    bassTone[74] = NOTE_C5;
    bassTone[75] = NOTE_CS5;
    bassTone[76] = 0;
    bassTone[77] = NOTE_D5;
    bassTone[78] = NOTE_FS5;
    bassTone[79] = NOTE_AS4;
    bassTone[80] = NOTE_C5;
    bassTone[81] = NOTE_CS5;
    bassTone[82] = 0;
    bassTone[83] = NOTE_D5;
    bassTone[84] = NOTE_FS5;
    bassTone[85] = NOTE_FS5;
    bassTone[86] = NOTE_D5;
    bassTone[87] = NOTE_G5;

    bassDuration[0] = 1;
    bassDuration[1] = 1;
    bassDuration[2] = 1;
    bassDuration[3] = 1;
    bassDuration[4] = 8;
    bassDuration[5] = 8;
    bassDuration[6] = 4;
    bassDuration[7] = 4;
    bassDuration[8] = 4;
    bassDuration[9] = 4;
    bassDuration[10] = 4;
    bassDuration[11] = 4;
    bassDuration[12] = 4;
    bassDuration[13] = 4;
    bassDuration[14] = 4;
    bassDuration[15] = 4;
    bassDuration[16] = 4;
    bassDuration[17] = 4;
    bassDuration[18] = 4;
    bassDuration[19] = 4;
    bassDuration[20] = 4;
    bassDuration[21] = 8;
    bassDuration[22] = 8;
    bassDuration[23] = 4;
    bassDuration[24] = 4;
    bassDuration[25] = 4;
    bassDuration[26] = 1;
    bassDuration[27] = 8;
    bassDuration[28] = 8;
    bassDuration[29] = 4;
    bassDuration[30] = 4;
    bassDuration[31] = 4;
    bassDuration[32] = 8;
    bassDuration[33] = 8;
    bassDuration[34] = 4;
    bassDuration[35] = 4;
    bassDuration[36] = 4;
    bassDuration[37] = 4;
    bassDuration[38] = 4;
    bassDuration[39] = 4;
    bassDuration[40] = 4;
    bassDuration[41] = 2;
    bassDuration[42] = 2;
    bassDuration[43] = 2;
    bassDuration[44] = 2;
    bassDuration[45] = 4;
    bassDuration[46] = 4;
    bassDuration[47] = 4;
    bassDuration[48] = 4;
    bassDuration[49] = 8;
    bassDuration[50] = 4;
    bassDuration[51] = 4;
    bassDuration[52] = 3;
    bassDuration[53] = 4;
    bassDuration[54] = 4;
    bassDuration[55] = 4;
    bassDuration[56] = 4;
    bassDuration[57] = 4;
    bassDuration[58] = 8;
    bassDuration[59] = 8;
    bassDuration[60] = 8;
    bassDuration[61] = 8;
    bassDuration[62] = 4;
    bassDuration[63] = 4;
    bassDuration[64] = 8;
    bassDuration[65] = 8;
    bassDuration[66] = 8;
    bassDuration[67] = 8;
    bassDuration[68] = 4;
    bassDuration[69] = 4;
    bassDuration[70] = 4;
    bassDuration[71] = 4;
    bassDuration[72] = 4;
    bassDuration[73] = 4;
    bassDuration[74] = 8;
    bassDuration[75] = 8;
    bassDuration[76] = 8;
    bassDuration[77] = 8;
    bassDuration[78] = 4;
    bassDuration[79] = 4;
    bassDuration[80] = 8;
    bassDuration[81] = 8;
    bassDuration[82] = 8;
    bassDuration[83] = 8;
    bassDuration[84] = 4;
    bassDuration[85] = 4;
    bassDuration[86] = 4;
    bassDuration[87] = 1;

    trackLengths[1] = 88;
    bpm = 240;

    currentSong = 2;
  }
}

void stopSong()
{
  for (int i = 0; i < songArrayLengths; i++) mainTone[i] = 0;
  for (int i = 0; i < songArrayLengths; i++) mainDuration[i] = 0;
  for (int i = 0; i < songArrayLengths; i++) bassTone[i] = 0;
  for (int i = 0; i < songArrayLengths; i++) bassDuration[i] = 0;

  for (int i = 0; i < playNoteIndexLength; i++) trackLengths[i] = 0;

  currentSong = 0;
  playNoteIndex[0] = 0;
  playNoteIndex[1] = 0;
  lastTime[0] = 0;
  lastTime[1] = 0;
  trackLengths[0] = 0;
  trackLengths[1] = 0;
  bpm = 0;
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

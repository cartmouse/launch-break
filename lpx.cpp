#include "lpx.h"

LPX::LPX(void)
{
  // Create sysex template for LPX
  sysex.push_back(240);
  sysex.push_back(0);
  sysex.push_back(32);
  sysex.push_back(41);
  sysex.push_back(2);
  sysex.push_back(12);
  sysex.push_back(0);
  sysex.push_back(0);
  sysex.push_back(247);

  // Create light message template
  lightMessage.push_back(144); // Note on
  lightMessage.push_back(0);   // Pad index
  lightMessage.push_back(0);   // Colour

  reset();
  portHandler.selectOutPort();
}

void LPX::reset(void)
{
  running = true;
  resetLong();
  resetShort();
  colourAllPads(black);
}

void LPX::resetLong()
{
  colourLongTrack(black);
  longTimeElapsed = 0;
  longBreakElapsed = 0;
  longRow = 8;
  longCol = 1;
  longNum = 0;
  longBreak = false;
}

void LPX::resetShort()
{
  colourShortTrack(black);
  shortTimeElapsed = 0;
  shortBreakElapsed = 0;
  shortRow = 7;
  shortCol = 2;
  shortNum = 0;
  shortBreak = false;
}

void LPX::toProgMode(void)
{
  sysex[6] = 14;
  sysex[7] = 1;
  portHandler.sendMessage(sysex);
}

void LPX::toLiveMode(void)
{
  sysex[6] = 14;
  sysex[7] = 0;
  portHandler.sendMessage(sysex);
}

void LPX::colourAllPads(int colour)
{
  lightMessage[2] = colour;
  for (int row = 1; row < 10; row++)
  {
    for (int col = 1; col < 10; col++)
    {
      lightMessage[1] = combineDigits(row, col);
      portHandler.sendMessage(lightMessage);
    }
  }
}

void LPX::colourLongTrack(int colour)
{
  int row = 8;
  int col = 1;
  lightMessage[2] = colour;
  for (int i = 0; i < 28; i++)
  {
    int testCase = (int)(i / 7);

    if (testCase == 0)
      col++;
    if (testCase == 1)
      row--;
    if (testCase == 2)
      col--;
    if (testCase == 3)
      row++;

    lightMessage[1] = combineDigits(row, col);
    portHandler.sendMessage(lightMessage);
  }
}

void LPX::colourShortTrack(int colour)
{
  int row = 7;
  int col = 2;
  lightMessage[2] = colour;
  for (int i = 0; i < 20; i++)
  {
    int testCase = (int)(i / 5);

    if (testCase == 0)
      col++;
    if (testCase == 1)
      row--;
    if (testCase == 2)
      col--;
    if (testCase == 3)
      row++;

    lightMessage[1] = combineDigits(row, col);
    portHandler.sendMessage(lightMessage);
  }
}

void LPX::colourPad(int row, int col, int colour)
{
  lightMessage[1] = combineDigits(row, col);
  lightMessage[2] = colour;
  portHandler.sendMessage(lightMessage);
}

int LPX::combineDigits(int a, int b)
{
  int times = 1;
  while (times <= b)
    times *= 10;
  return a * times + b;
}

void LPX::increment(int testNum, int padNum, int *row, int *col)
{
  int testCase = (int)(testNum / padNum);

  if (testCase == 0)
    (*col)++;
  if (testCase == 1)
    (*row)--;
  if (testCase == 2)
    (*col)--;
  if (testCase == 3)
    (*row)++;
}

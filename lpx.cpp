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

  portHandler.selectOutPort();
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

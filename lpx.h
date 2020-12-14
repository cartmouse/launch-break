
#include <iostream>
#include <vector>
#include "porthandler.h"

class LPX
{
  std::vector<unsigned char> sysex;
  std::vector<unsigned char> lightMessage;
  PortHandler portHandler;

  // Colours
  int red = 5;
  int green = 21;
  int blue = 37;
  int black = 0;
  int white = 3;
  int yellow = 13;
  int purple = 45;
  int orange = 61;
  int pink = 53;

public:
  bool running, longBreak, shortBreak;
  int longTimeElapsed, shortTimeElapsed, longBreakElapsed, shortBreakElapsed;
  int longRow, longCol, shortRow, shortCol;
  int longNum, shortNum;
  LPX(void);
  void reset(void);
  void resetLong(void);
  void resetShort(void);
  void toProgMode(void);
  void toLiveMode(void);
  void colourAllPads(int colour);
  void colourLongTrack(int colour);
  void colourShortTrack(int colour);
  void colourPad(int row, int col, int colour);
  int combineDigits(int digit1, int digit2);
  void increment(int testNum, int padNum, int *row, int *col);

  // Get colours
  int Red(void) { return red; };
  int Blue(void) { return blue; };
  int Green(void) { return green; };
  int Black(void) { return black; };
  int White(void) { return white; };
  int Yellow(void) { return yellow; };
  int Purple(void) { return purple; };
  int Orange(void) { return orange; };
  int Pink(void) { return pink; };
};
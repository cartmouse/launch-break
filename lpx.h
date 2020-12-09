
#include <iostream>
#include <vector>
#include "porthandler.h"

class LPX
{
  std::vector<unsigned char> sysex;
  std::vector<unsigned char> lightMessage;
  PortHandler portHandler;

public:
  LPX(void);
  void toProgMode(void);
  void toLiveMode(void);
  void colourAllPads(int colour);
  void colourPad(int row, int col, int colour);
  int combineDigits(int digit1, int digit2);
};
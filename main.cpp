#include "lpx.h"
#include "colours.h"

int main()
{
  std::vector<unsigned char> message;
  Colours colours;
  LPX lpx;

  int timeMS = 5000;

  int interval = timeMS / 28;

  lpx.toProgMode();

  lpx.colourPad(8, 5, colours.Blue());
  SLEEP(interval);
  lpx.colourPad(8, 6, colours.Blue());
  SLEEP(interval);
  lpx.colourPad(8, 7, colours.Blue());
  SLEEP(interval);
  lpx.colourPad(8, 8, colours.Blue());
  SLEEP(interval);

  lpx.toLiveMode();

  return 0;
}
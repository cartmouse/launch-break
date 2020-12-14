#include <iostream>
#include <cstdlib>
#include <string>
#include "lpx.h"

int main(int argc, char *argv[])
{
  int longTimeMins = 1;
  int longBreakMins = 1;
  int shortTimeMins = 1;
  int shortBreakSecs = 15;

  if (argc > 1)
  {
    longTimeMins = std::stoi(argv[1]);
    shortTimeMins = std::stoi(argv[2]);
    longBreakMins = std::stoi(argv[3]);
    shortBreakSecs = std::stoi(argv[4]);
  }

  int longTimeMS = longTimeMins * 60000;
  int shortTimeMS = shortTimeMins * 60000;
  int longTimeS = longTimeMins * 60;
  int shortTimeS = shortTimeMins * 60;

  int longInterval = longTimeS / 28;
  int shortInterval = shortTimeS / 20;

  LPX *lpx = new LPX();

  // Init and light control pads
  lpx->toProgMode();
  lpx->colourAllPads(lpx->Black());
  lpx->colourPad(5, 4, lpx->Green());
  lpx->colourPad(5, 5, lpx->Red());
  lpx->colourPad(4, 4, lpx->Blue());
  lpx->colourPad(4, 5, lpx->Yellow());

  std::cout << "Long time: " << longTimeS << "s\n";
  std::cout << "Short time: " << shortTimeS << "s\n";

  while (lpx->running)
  {
    SLEEP(1000);

    // Check for long time increment
    if (lpx->longTimeElapsed % longInterval == 0)
    {
      // Check if break active
      if (lpx->longBreak)
      {
        lpx->colourLongTrack(lpx->Green());

        if (lpx->longBreakElapsed > longBreakMins * 60)
          lpx->resetLong();
      }
      else
      {
        if (lpx->longTimeElapsed != 0 && lpx->longTimeElapsed % longTimeS == 0)
          lpx->longBreak = true;
        else
        {
          lpx->colourPad(lpx->longRow, lpx->longCol, lpx->Purple());
          lpx->increment(lpx->longNum, 7, &lpx->longRow, &lpx->longCol);
          lpx->longNum++;
        }
      }
    }

    // Check for short time increment
    if (lpx->shortTimeElapsed % shortInterval == 0)
    {
      if (lpx->shortBreak)
      {
        lpx->colourShortTrack(lpx->Green());

        if (lpx->shortBreakElapsed > shortBreakSecs)
          lpx->resetShort();
      }
      else
      {
        if (lpx->shortTimeElapsed != 0 && lpx->shortTimeElapsed % shortTimeS == 0)
          lpx->shortBreak = true;
        else
        {
          lpx->colourPad(lpx->shortRow, lpx->shortCol, lpx->Pink());
          lpx->increment(lpx->shortNum, 5, &lpx->shortRow, &lpx->shortCol);
          lpx->shortNum++;
        }
      }
    }

    // Increment elapsed and check for end
    lpx->longTimeElapsed++;
    lpx->shortTimeElapsed++;

    if (lpx->longBreak)
      lpx->longBreakElapsed++;

    if (lpx->shortBreak)
      lpx->shortBreakElapsed++;
  }

  SLEEP(5000);

  lpx->toLiveMode();
  delete lpx;

  return 0;
}
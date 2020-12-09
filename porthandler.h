#include <iostream>
#include <cstdlib>
#include <string>
#include "RtMidi.h"
#include <signal.h>
#include <windows.h>
#define SLEEP(milliseconds) Sleep((DWORD)milliseconds)

class PortHandler
{
  RtMidiIn *midiin = 0;
  RtMidiOut *midiout = 0;

  unsigned int numInPorts, numOutPorts;
  int longTimeMs, shortTimerMs;

public:
  PortHandler(void);
  ~PortHandler();
  void getPortCount(void);
  void displayInputPorts(void);
  void displayOutputPorts(void);
  void selectOutPort(void);
  void sendMessage(std::vector<unsigned char> message);
};
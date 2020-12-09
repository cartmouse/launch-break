#include "porthandler.h"

PortHandler::PortHandler(void)
{
  try
  {
    // RtMidi In and Out init
    midiin = new RtMidiIn();
    midiout = new RtMidiOut();

    getPortCount();
  }
  catch (RtMidiError &error)
  {
    error.printMessage();
    exit(EXIT_FAILURE);
  }
}

PortHandler::~PortHandler()
{
  delete midiin;
  delete midiout;
}

void PortHandler::getPortCount(void)
{
  numInPorts = midiin->getPortCount();
  numOutPorts = midiout->getPortCount();
}

void PortHandler::displayInputPorts(void)
{
  std::cout << "\nInput ports: " << std::endl;
  std::string portName;
  for (unsigned int i = 0; i < numInPorts; i++)
  {
    try
    {
      portName = midiin->getPortName(i);
    }
    catch (RtMidiError &error)
    {
      error.printMessage();
    }
    std::cout << i << ": " << portName << std::endl;
  }
}

void PortHandler::displayOutputPorts(void)
{
  std::string portName;
  std::cout << "\nOutput ports: " << std::endl;
  for (unsigned int i = 0; i < numOutPorts; i++)
  {
    try
    {
      portName = midiout->getPortName(i);
    }
    catch (RtMidiError &error)
    {
      error.printMessage();
    }
    std::cout << i << ": " << portName << std::endl;
  }
}

void PortHandler::selectOutPort(void)
{
  int portNum;
  displayOutputPorts();
  std::cout << "\nSelect output port: " << std::endl;
  std::cin >> portNum;
  midiout->openPort(portNum);
}

void PortHandler::sendMessage(std::vector<unsigned char> message)
{
  midiout->sendMessage(&message);
}
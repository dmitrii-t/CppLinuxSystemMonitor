#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"

using std::string;
using std::vector;

class System {
 public:
  System(LinuxParser& parser) : parser_(parser){};

  // reads all the system and prcesses files into memory
  void Read();

  Processor& Cpu();               // TODO: See src/system.cpp
  vector<Process>& Processes();   // TODO: See src/system.cpp
  float MemoryUtilization();      // TODO: See src/system.cpp
  long UpTime();                  // TODO: See src/system.cpp
  int TotalProcesses();           // TODO: See src/system.cpp
  int RunningProcesses();         // TODO: See src/system.cpp
  std::string Kernel();           // TODO: See src/system.cpp
  std::string OperatingSystem();  // TODO: See src/system.cppProcess
                                  // process{pid, parser_.Command(pid), stats}

 private:
  LinuxParser& parser_;
  Processor cpu_ = {};
  vector<Process> processes_ = {};
  long int system_uptime_;
};

#endif
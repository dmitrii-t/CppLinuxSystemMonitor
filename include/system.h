#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "linux_parser.h"
#include "memory.h"
#include "process.h"
#include "processor.h"

using std::string;
using std::vector;

class System {
 public:
  System(LinuxParser& parser) : parser_(parser){};

  // reads all the system and prcesses files into memory
  void Read();

  Processor& Cpu();               // See src/system.cpp
  vector<Process>& Processes();   // See src/system.cpp
  float MemoryUtilization();      // See src/system.cpp
  long int UpTime();              // See src/system.cpp
  int TotalProcesses();           // See src/system.cpp
  int RunningProcesses();         // See src/system.cpp
  std::string Kernel();           // See src/system.cpp
  std::string OperatingSystem();  // See src/system.cpp

 private:
  LinuxParser& parser_;

  Processor cpu_{};
  Ram ram_{};
  int procs_running_;
  int procs_total_;
  long int system_uptime_sec_;
  long int start_time_sec_;
  string kernel_;
  string os_;
  vector<Process> processes_{};
};

#endif
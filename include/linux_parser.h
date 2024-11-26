#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

#include "memory_stats.h"

using std::string;

class LinuxParser {
 public:
  // System
  MemoryStats ReadMemoryStats();
  long UpTime();
  std::vector<int> Pids();
  int TotalProcesses();
  int RunningProcesses();
  string OperatingSystem();
  string Kernel();

  // CPU
  enum CPUStates {
    kUser_ = 0,
    kNice_,
    kSystem_,
    kIdle_,
    kIOwait_,
    kIRQ_,
    kSoftIRQ_,
    kSteal_,
    kGuest_,
    kGuestNice_
  };
  std::vector<string> CpuUtilization();
  long Jiffies();
  long ActiveJiffies();
  long ActiveJiffies(int pid);
  long IdleJiffies();

  // Processes
  string Command(int pid);
  string Ram(int pid);
  string Uid(int pid);
  string User(int pid);
  long int UpTime(int pid);

  // Paths
  string kProcDirectory{"/proc/"};
  string kCmdlineFilename{"/cmdline"};
  string kCpuinfoFilename{"/cpuinfo"};
  string kStatusFilename{"/status"};
  string kStatFilename{"/stat"};
  string kUptimeFilename{"/uptime"};
  string kMeminfoFilename{"/meminfo"};
  string kVersionFilename{"/version"};
  string kOSPath{"/etc/os-release"};
  string kPasswordPath{"/etc/passwd"};
};  // class LinuxParser

#endif
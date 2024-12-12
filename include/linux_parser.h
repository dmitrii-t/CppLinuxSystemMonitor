#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <cmath>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

#include "processor.h"

using std::string;
using std::unordered_map;
using std::vector;

struct Cpu {
  float Utilization() {
    return round((ActiveTime() * 1.0 / TotalTime() * 1.0) * 1000) / 1000;
  }
  int ActiveTime() {
    return user + nice + system + irq + softirq + steal + guest + guest_nice;
  }
  int TotalTime() {
    return user + nice + system + idle + iowait + irq + softirq + steal +
           guest + guest_nice;
  }

  string name;
  int user;
  int nice;
  int system;
  int idle;
  int iowait;
  int irq;
  int softirq;
  int steal;
  int guest;
  int guest_nice;
};

struct SystemStats {
  vector<Cpu> cpus;
  int procs_total;
  int procs_running;
  int procs_blocked;
};

struct ProcessStats {
  long int user_time;
  long int system_time;
  long int child_user_time;
  long int child_system_time;
  long int start_time;
};

struct ProcessStatus {
  string ram;
  int uid;
};

struct MemoryStats {
  int TotalUsedMemory() { return MemTotal - MemFree; }
  int NonCacheMemory() { return TotalUsedMemory() - Buffers - Cached; }
  int CachedMemory() { return Cached + SReclaimable - Shmem; }
  int Swap() { return SwapTotal - SwapFree; }
  int MemTotal;
  int MemFree;
  int MemAvailable;
  int Buffers;
  int Cached;
  int SReclaimable;
  int Shmem;
  int SwapFree;
  int SwapTotal;
};

// LinuxParser class is designed around the data files to optimize the number of
// reads
class LinuxParser {
 public:
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

  // System
  // float MemoryUtilization();
  long UpTime();
  std::vector<int> Pids();
  // int TotalProcesses();
  // int RunningProcesses();
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
  // std::vector<string> CpuUtilization();
  // long Jiffies();
  // long ActiveJiffies();
  // long ActiveJiffies(int pid);
  // long IdleJiffies();

  // Processes
  string Command(int pid);
  // string Ram(int pid);
  // string Uid(int pid);
  // string User(int pid);
  // long int UpTime(int pid);

  // Read system files
  MemoryStats ReadMemoryStats();
  SystemStats ReadSystemStats();
  unordered_map<int, string> ReadUserMap();

  // Read process files
  ProcessStats ReadProcessStats(int);
  ProcessStatus ReadProcessStatus(int);

};  // class LinuxParser
#endif
#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <cmath>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

#include "processor.h"

using std::string;
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
  int ram;
  int uid;
};

struct MemoryStats {
  int64_t TotalUsedMemory() { return MemTotal - MemFree; }
  int64_t NonCacheMemory() { return TotalUsedMemory() - Buffers - Cached; }
  int64_t CachedMemory() { return Cached + SReclaimable - Shmem; }
  int64_t Swap() { return SwapTotal - SwapFree; }
  int64_t MemTotal;
  int64_t MemFree;
  int64_t MemAvailable;
  int64_t Buffers;
  int64_t Cached;
  int64_t SReclaimable;
  int64_t Shmem;
  int64_t SwapFree;
  int64_t SwapTotal;
};

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
  MemoryStats ReadMemoryStats();
  SystemStats ReadSystemStats();
  ProcessStats ReadProcessStats(int pid);

  float MemoryUtilization();
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

};  // class LinuxParser
#endif
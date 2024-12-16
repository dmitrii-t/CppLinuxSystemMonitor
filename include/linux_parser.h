#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <cmath>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

using std::string;
using std::unordered_map;
using std::vector;

struct Cpu {
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
  long int btime;
};

struct ProcessStats {
  long int user_time;
  long int system_time;
  long int child_user_time;
  long int child_system_time;
  long int start_time;
};

struct ProcessStatus {
  long int ram;
  int uid;
};

struct MemoryStats {
  int mem_total;
  int mem_free;
  int mem_available;
  int buffers;
  int cached;
  int sreclaimable;
  int shmem;
  int swap_free;
  int swap_total;
};

// LinuxParser class is designed around the system data files
// to optimize the number of reads
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
  long UpTime();
  std::vector<int> Pids();
  string OperatingSystem();
  string Kernel();

  MemoryStats ReadMemoryStats();
  SystemStats ReadSystemStats();
  unordered_map<int, string> ReadUserMap();

  // Processes
  string Command(int pid);

  ProcessStats ReadProcessStats(int);
  ProcessStatus ReadProcessStatus(int);

};  // class LinuxParser
#endif
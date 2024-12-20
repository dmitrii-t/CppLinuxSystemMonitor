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

// Structs to read /proc/stat
struct Cpu;
struct SystemStats {
  vector<Cpu> cpus;
  int procs_total;
  int procs_running;
  long int btime;
};

//  Struct to read /proc/meminfo
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

// Struct to read /proc/<pid>/stat
struct ProcessStats {
  long int user_time;
  long int system_time;
  long int child_user_time;
  long int child_system_time;
  long int start_time;
};

// Struct to read /proc/<pid>/status
struct ProcessStatus {
  string state;
  long int ram{-1};
  int uid{-1};
};

// Parser class to read Linux's /proc files; reads files into intermediate
// structs.
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
#include "system.h"

#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

void System::Read() {
  // Read system uptime
  system_uptime_ = parser_.UpTime();
  auto user_map = parser_.ReadUserMap();

  // Create processes
  auto pids = parser_.Pids();
  processes_.clear();
  processes_.reserve(pids.size());

  for (auto pid : pids) {
    // Read process data
    auto stats = parser_.ReadProcessStats(pid);
    auto status = parser_.ReadProcessStatus(pid);
    int uptime = system_uptime_ - stats.start_time;
    string cmd = parser_.Command(pid);
    string username = user_map[status.uid];

    // Create process model
    Process process{pid,
                    cmd,
                    status.uid,
                    username,
                    status.ram,
                    stats.user_time,
                    stats.system_time,
                    stats.child_user_time,
                    stats.child_system_time,
                    stats.start_time,
                    uptime};

    processes_.push_back(process);
  }
}

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return string(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return 0.0; }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return string(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return 0; }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return 0; }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return system_uptime_; }
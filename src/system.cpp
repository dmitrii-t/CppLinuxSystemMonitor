#include "system.h"
#include "format.h"
#include "linux_parser.h"
#include "process.h"
#include "processor.h"

#include <cstddef>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using std::cout;
using std::set;
using std::size_t;
using std::string;
using std::vector;

void System::Read() {
  // Read system data
  os_ = parser_.OperatingSystem();
  kernel_ = parser_.Kernel();

  // System processes data
  auto system = parser_.ReadSystemStats();
  procs_running_ = system.procs_running;
  procs_total_ = system.procs_total;
  start_time_sec_ = system.btime;

  // System Cpu
  auto cpu0 = system.cpus[0];
  cpu_ = Processor{
      cpu0.user, cpu0.nice,    cpu0.system, cpu0.idle,  cpu0.iowait,
      cpu0.irq,  cpu0.softirq, cpu0.steal,  cpu0.guest, cpu0.guest_nice,
  };

  // System Ram
  auto memory = parser_.ReadMemoryStats();
  ram_ = Ram{memory.mem_total, memory.mem_free,  memory.mem_available,
             memory.buffers,   memory.cached,    memory.sreclaimable,
             memory.shmem,     memory.swap_free, memory.swap_total};

  // System Uptime
  system_uptime_sec_ = parser_.UpTime();
  auto user_map = parser_.ReadUserMap();

  // System processes detail
  auto pids = parser_.Pids();
  processes_.clear();
  processes_.reserve(pids.size());

  for (auto pid : pids) {
    // Read process data
    auto stats = parser_.ReadProcessStats(pid);
    auto status = parser_.ReadProcessStatus(pid);
    auto command = parser_.Command(pid);
    auto username = user_map[status.uid];
    auto proc_start_time = start_time_sec_ + stats.start_time / CLK_TICKS;

    // Create process model
    Process process{pid,
                    command,
                    status.uid,
                    username,
                    status.ram,
                    stats.user_time,
                    stats.system_time,
                    stats.child_user_time,
                    stats.child_system_time,
                    proc_start_time};

    processes_.push_back(process);
  }
}

// DOONE: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// DOONE: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// DOONE: Return the system's kernel identifier (string)
std::string System::Kernel() { return kernel_; }

// DOONE: Return the system's memory utilization
float System::MemoryUtilization() { return ram_.Utilization(); }

// DOONE: Return the operating system name
std::string System::OperatingSystem() { return os_; }

// DOONE: Return the number of processes actively running on the system
int System::RunningProcesses() { return procs_running_; }

// DOONE: Return the total number of processes on the system
int System::TotalProcesses() { return procs_total_; }

// DOONE: Return the number of seconds since the system started running
long int System::UpTime() { return system_uptime_sec_; }
#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using std::cerr;
using std::cout;
using std::ifstream;
using std::stof;
using std::string;
using std::to_string;
using std::unordered_map;
using std::vector;

// An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// Read kernel data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

vector<int> LinuxParser::Pids() {
  vector<int> pids;
  const std::filesystem::path proc_path{kProcDirectory};

  std::error_code err;
  for (const auto& entry :
       std::filesystem::directory_iterator(proc_path, err)) {
    string filename = entry.path().filename().string();

    if (std::all_of(filename.begin(), filename.end(), isdigit)) {
      try {
        pids.push_back(std::stoi(filename));
      } catch (const std::exception& e) {
        cout << "warning: failed to parse " << filename << " as " << e.what()
             << '\n';
      }
    }
  }

  if (err) {
    cerr << "fail to access directory " << proc_path << " as " << err.message()
         << '\n';
  }

  std::sort(pids.begin(), pids.end());
  return pids;
}

// TODO: Read and return the system memory utilization
// float LinuxParser::MemoryUtilization() { return 0.0; }

// Read the system uptime
long LinuxParser::UpTime() {
  double uptime, idle;
  string line;
  ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> uptime >> idle;
    }
  }
  return uptime;  // seconds
}

// TODO: Read and return the number of jiffies for the system
// long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
// long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
// long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
// long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
// vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
// int LinuxParser::TotalProcesses() { return 0; }

// TODO: Read and return the number of running processes
// int LinuxParser::RunningProcesses() { return 0; }

// Read the command associated with a process
string LinuxParser::Command(int pid) {
  string cmd, line;
  ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      cmd = line;
      std::replace(cmd.begin(), cmd.end(), '\0', ' ');
    }
  }
  return cmd;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
// string LinuxParser::Ram(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
// string LinuxParser::Uid(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
// string LinuxParser::User(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
// long LinuxParser::UpTime(int pid [[maybe_unused]]) { return 0; }

// Read system meminfo
MemoryStats LinuxParser::ReadMemoryStats() {
  // The map below links the keys in the file to the struct instance fields
  MemoryStats memory;
  unordered_map<string, int&> memoryMap = {
      {"MemTotal", memory.mem_total},
      {"MemFree", memory.mem_free},
      {"MemAvailable", memory.mem_available},
      {"Buffers", memory.buffers},
      {"Cached", memory.cached},
      {"SReclaimable", memory.sreclaimable},
      {"Shmem", memory.shmem},
      {"SwapFree", memory.swap_free},
      {"SwapTotal", memory.swap_total},
  };

  string line;
  string key;
  int value;
  ifstream filestream(kProcDirectory + kMeminfoFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        auto it = memoryMap.find(key);
        if (it != memoryMap.end()) {
          it->second = value;
        }
      }
    }
  }

  return memory;
}

// Read system stat file
SystemStats LinuxParser::ReadSystemStats() {
  SystemStats system;
  string name;
  string line;
  ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      if (linestream >> name) {
        // read CPUs
        if (name.length() >= 3 && name.substr(0, 3) == "cpu") {
          // sets just the first menber of the struct which is name
          Cpu cpu{name};

          // continue reading the stream to the struct
          if (linestream >> cpu.user >> cpu.nice >> cpu.system >> cpu.idle >>
              cpu.iowait >> cpu.irq >> cpu.softirq >> cpu.steal >> cpu.guest >>
              cpu.guest_nice) {
            // append when all the reads has happened
            system.cpus.push_back(cpu);
          }
        }
        // read btime (system start time)
        if (name.length() >= 5 && name.substr(0, 5) == "btime") {
          linestream >> system.btime;
        }
        // read processes total
        if (name.length() >= 9 && name.substr(0, 9) == "processes") {
          linestream >> system.procs_total;
        }
        // read processes running
        if (name.length() >= 13 && name.substr(0, 13) == "procs_running") {
          linestream >> system.procs_running;
        }
      }
    }
  }
  return system;
}

// Read process' status file
ProcessStatus LinuxParser::ReadProcessStatus(int pid) {
  ProcessStatus status;
  string line, key;
  string path{kProcDirectory + to_string(pid) + kStatusFilename};
  ifstream filestream(path);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      if (linestream >> key) {
        // read RAM
        if (key == "VmSize:") {
          string units;
          linestream >> status.ram >> units;

          // Convert to bytes based on the units
          long int unit_mult;
          if (units == "kB" || units == "KB") {
            unit_mult = 1024;
          } else if (units == "MB") {
            unit_mult = 1024 * 1024;
          } else if (units == "GB") {
            unit_mult = 1024 * 1024 * 1024;
          } else if (units == "TB") {
            unit_mult = 1024.0 * 1024 * 1024 * 1024;
          }

          status.ram *= unit_mult;
        }

        // read UID
        if (key == "Uid:") {
          linestream >> status.uid;
        }
      }
    }
  }
  return status;
}

// Read process'stat file
ProcessStats LinuxParser::ReadProcessStats(int pid) {
  ProcessStats stats;
  string line, _;
  ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      // skip the first 13 numbers
      for (int i = 0; i < 13; i++) {
        linestream >> _;
      }

      // read the jiffies
      linestream >> stats.user_time;          // utime (14)
      linestream >> stats.system_time;        // stime (15)
      linestream >> stats.child_user_time;    // cutime (16)
      linestream >> stats.child_system_time;  // cstime (17)

      // skip the next numbers
      for (int i = 16; i < 20; i++) {
        linestream >> _;
      }

      // read the start time (22)
      linestream >> stats.start_time;
    }
  }
  return stats;
}

// Read user map uid => username
unordered_map<int, string> LinuxParser::ReadUserMap() {
  unordered_map<int, string> result;
  string line, username, uid, _;

  ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream iss(line);
      if (std::getline(iss, username, ':') && std::getline(iss, _, ':') &&
          std::getline(iss, uid, ':')) {
        result[std::stoi(uid)] = username;
      }
    }
  }
  return result;
}
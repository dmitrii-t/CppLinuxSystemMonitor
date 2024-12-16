#include "process.h"

#include <cctype>
#include <cmath>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "format.h"

using std::cout;
using std::string;
using std::to_string;
using std::vector;

// Return this process's ID
int Process::Pid() { return pid_; }

// Return this process's CPU utilization
float Process::CpuUtilization() const {
  long int total_time =
      user_time_ + system_time_ + child_user_time_ + child_system_time_;
  float utilization = (total_time / CLK_TICKS) / UpTime();
  return round(100.f * utilization) / 100.f;
}

// Return the command that generated this process
string Process::Command() { return cmd_; }

// Return this process's memory utilization
string Process::Ram() {
  // Formasts in MB
  return (ram_ < 0) ? "n/a" : to_string((ram_ / 1024) / 1024);
}

// Return the user (name) that generated this process
string Process::User() { return username_; }

// Return the age of this process (in seconds)
long int Process::UpTime() const {
  auto currecnt_time_sec = time(nullptr);
  return currecnt_time_sec - start_time_sec_;
}

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { return ram_ < a.ram_; }
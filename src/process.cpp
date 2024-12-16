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

// DONE: Return this process's ID
int Process::Pid() { return pid_; }

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() const {
  long int total_time =
      user_time_ + system_time_ + child_user_time_ + child_system_time_;
  float utilization = (total_time / HERTZ) / UpTime();
  return round(100.f * utilization) / 100.f;
}

// DONE: Return the command that generated this process
string Process::Command() { return cmd_; }

// DONE: Return this process's memory utilization
string Process::Ram() {
  // Formasts in MB
  return to_string((ram_ / 1024) / 1024);
}

// TODO: Return the user (name) that generated this process
string Process::User() { return username_; }

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() const {
  auto currecnt_time_sec = time(nullptr);
  return currecnt_time_sec - start_time_sec_;
}

// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
  return CpuUtilization() > a.CpuUtilization();
}
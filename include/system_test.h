#pragma once

#include <algorithm>

using std::find_if;

void TestSystemReadProcessesSuccessfully() {
  LinuxParser parser;
  parser.kProcDirectory = "./test/";

  System system{parser};
  system.Read();

  auto procs = system.Processes();
  auto itr = find_if(procs.begin(), procs.end(),
                     [](Process& p) { return p.Pid() == 1; });

  assert(itr != procs.end());
  auto proc = *itr;
  assert(proc.Pid() == 1);
  assert(proc.Command() == "/sbin/init splash ");
  assert(proc.User() == "root");
  assert(proc.CpuUtilization() == 0);
  assert(proc.Ram() == "23328kB");
  assert(proc.UpTime() == 97);
}

void TestSystem() { TestSystemReadProcessesSuccessfully(); }

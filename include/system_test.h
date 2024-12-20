#pragma once

#include <algorithm>

using std::find_if;

void TestSystemReadProcessesSuccessfully() {
  // given
  LinuxParser parser;
  parser.kProcDirectory = "./test/";  // local project directory

  // when
  System system{parser};
  system.Read();

  auto procs = system.Processes();
  auto itr = find_if(procs.begin(), procs.end(),
                     [](Process& p) { return p.Pid() == 1; });

  assert(itr != procs.end());
  auto proc = *itr;

  // then
  assert(proc.Pid() == 1);
  assert(proc.Command() == "/sbin/init splash ");
  assert(proc.User() == "root");
  assert(proc.CpuUtilization() == 0);
  assert(proc.Ram() == "22");
  assert(system.MemoryUtilization() == 0.68f);
  assert(system.Cpu().Utilization() == 0.05f);
  assert(system.UpTime() == 9833);
  assert(system.TotalProcesses() == 9127);
  assert(system.RunningProcesses() == 3);
  assert(system.Kernel() == "6.8.0-49-generic");
}

void TestSystemAll() { TestSystemReadProcessesSuccessfully(); }

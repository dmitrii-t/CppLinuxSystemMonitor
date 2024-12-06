#pragma once

#include <cassert>
#include <iostream>
#include <string>

#include "linux_parser.h"
#include "processor.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

void TestReadMemoryStats() {
  LinuxParser parser;
  parser.kProcDirectory = "./test/";  // local project directory

  MemoryStats memory = parser.ReadMemoryStats();
  assert(memory.MemTotal == 8083696);
  assert(memory.TotalUsedMemory() == 5537196);
  assert(memory.NonCacheMemory() == 2794944);
  assert(memory.CachedMemory() == 2532924);
  assert(memory.Swap() == 0);
}

void TestKernel() {
  LinuxParser parser;
  parser.kProcDirectory = "./test/";  // local project directory
  assert(parser.Kernel() == "6.8.0-49-generic");
}

void TestOperatingSystem() {
  LinuxParser parser;
  parser.kOSPath = "./test/os-release";  // local project directory
  assert(parser.OperatingSystem() == "Ubuntu 24.04.1 LTS");
}

void TestUpTime() {
  LinuxParser parser;
  parser.kProcDirectory = "./test/";   // local project directory
  assert(parser.UpTime() == 9833790);  // up time in millis
}

void TestReadSystemStats() {
  Cpu expected{"cpu", 17408, 30, 7353, 526771, 333, 0, 253, 0, 0, 0};
  LinuxParser parser;
  parser.kProcDirectory = "./test/";  // local project directory

  SystemStats system{parser.ReadSystemStats()};
  assert(system.cpus[0].name == expected.name);
  assert(system.cpus[0].user == expected.user);
  assert(system.cpus[0].nice == expected.nice);
  assert(system.cpus[0].system == expected.system);
  assert(system.cpus[0].iowait == expected.iowait);
  assert(system.cpus[0].irq == expected.irq);
  assert(system.cpus[0].softirq == expected.softirq);
  assert(system.cpus[0].steal == expected.steal);
  assert(system.cpus[0].guest == expected.guest);
  assert(system.cpus[0].guest_nice == expected.guest_nice);
  assert(system.cpus[0].ActiveTime() == 25044);
  assert(system.cpus[0].TotalTime() == 552148);
  assert(system.cpus[0].Utilization() == 0.045f);
  assert(system.procs_total == 9127);
  assert(system.procs_running == 3);
  assert(system.procs_blocked == 0);
}

void TestReadProcessStatus() {
  LinuxParser parser;
  parser.kProcDirectory = "./test/";  // local project directory

  ProcessStatus stats{parser.ReadProcessStatus(1)};
  assert(stats.ram == 23312);
  assert(stats.uid == 0);
}

void TestPids() {
  vector<int> expected{2, 15, 9, 1, 24, 66};
  LinuxParser parser;
  parser.kProcDirectory = "./test/";
  auto pids = parser.Pids();
  assert(pids == expected);
}

void TestCommand() {
  string expected{"/sbin/init splash "};
  LinuxParser parser;
  parser.kProcDirectory = "./test/";
  auto cmd = parser.Command(1);
  assert(cmd == expected);
}

void TestReadProcessStats() {
  LinuxParser parser;
  parser.kProcDirectory = "./test/";
  auto stats = parser.ReadProcessStats(1);
  assert(stats.user == 58);
  assert(stats.system == 220);
  assert(stats.child_user == 401);
  assert(stats.child_system == 680);
  assert(stats.start_time == 121);
}

void TestLinuxParser() {
  TestReadMemoryStats();
  TestKernel();
  TestUpTime();
  TestReadSystemStats();
  TestReadProcessStats();
  TestReadProcessStatus();
  TestCommand();
  cout << "LinuxParser: All tests passed!" << endl;
}

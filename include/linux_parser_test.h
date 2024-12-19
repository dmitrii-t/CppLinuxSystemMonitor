#pragma once

#include <cassert>
#include <iostream>
#include <string>

#include "linux_parser.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

void TestReadMemoryStats() {
  LinuxParser parser;
  parser.kProcDirectory = "./test/";  // local project directory

  MemoryStats memory = parser.ReadMemoryStats();
  assert(memory.mem_total == 8083696);
  assert(memory.mem_free == 2546500);
  assert(memory.mem_available == 4873872);
  assert(memory.buffers == 56376);
  assert(memory.cached == 2685876);
  assert(memory.sreclaimable == 82572);
  assert(memory.shmem == 235524);
  assert(memory.swap_free == 0);
  assert(memory.swap_total == 0);
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
  parser.kProcDirectory = "./test/";  // local project directory
  assert(parser.UpTime() == 9833);    // up time in millis
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
  assert(system.procs_total == 9127);
  assert(system.procs_running == 3);
}

void TestReadProcessStatus() {
  LinuxParser parser;
  parser.kProcDirectory = "./test/";  // local project directory

  ProcessStatus pstatus{parser.ReadProcessStatus(1)};
  // cout << "pstatus.ram=" << pstatus.ram << '\n';
  assert(pstatus.ram == 23887872);
  assert(pstatus.uid == 0);
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
  assert(stats.user_time == 40);
  assert(stats.system_time == 240);
  assert(stats.child_user_time == 2114);
  assert(stats.child_system_time == 4725);
  assert(stats.start_time == 122);
}

void TestReadUsers() {
  LinuxParser parser;
  auto users = parser.ReadUserMap();
  assert(users[0] == "root");
}

void TestLinuxParserAll() {
  TestReadMemoryStats();
  TestKernel();
  TestUpTime();
  TestReadSystemStats();
  TestReadProcessStats();
  TestReadProcessStatus();
  TestCommand();
}

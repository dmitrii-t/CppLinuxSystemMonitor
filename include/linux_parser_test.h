#pragma once

#include <cassert>
#include <iostream>
#include <string>

#include "linux_parser.h"
#include "memory_stats.h"

using std::string;

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

void OperatingSystem() {
  LinuxParser parser;
  parser.kOSPath = "./test/os-release";  // local project directory
  assert(parser.OperatingSystem() == "Ubuntu 24.04.1 LTS");
}

void TestLinuxParser() {
  TestReadMemoryStats();
  TestKernel();
  std::cout << "LinuxParser: All tests passed!" << std::endl;
}
#pragma once

#include <cassert>
#include <iostream>
#include "linux_parser.h"

void TestParseMemoryUtilization() {
  assert(LinuxParser::ParseMemoryUtilization("./proc/meminfo").MemTotal == 8083696);
  assert(LinuxParser::ParseMemoryUtilization("./proc/meminfo").TotalUsedMemory() == 5537196);
  assert(LinuxParser::ParseMemoryUtilization("./proc/meminfo").NonCacheMemory() == 2794944);
  assert(LinuxParser::ParseMemoryUtilization("./proc/meminfo").CachedMemory() == 2532924);
  assert(LinuxParser::ParseMemoryUtilization("./proc/meminfo").Swap() == 0);
}

void TestLinuxParser() {
  TestParseMemoryUtilization();
  std::cout << "LinuxParser: All tests passed!" << std::endl;
}
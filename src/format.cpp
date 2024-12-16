#include "format.h"

#include <cstdio>
#include <string>

using std::string;

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long int seconds) {
  long hours = seconds / 3600;
  long mins = (seconds % 3600) / 60;
  long secs = seconds % 60;

  char buffer[9];  // HH:MM:SS + null terminator
  snprintf(buffer, sizeof(buffer), "%02ld:%02ld:%02ld", hours, mins, secs);
  return string(buffer);
}
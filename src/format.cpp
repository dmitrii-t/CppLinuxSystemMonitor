#include "format.h"

#include <cstdio>
#include <string>

using std::string;

// Format time in seconds to HH:MM:SS string
// ARGS: Long int measuring seconds
// RETURNS: string in HH:MM:SS format
string Format::ElapsedTime(long int seconds) {
  long hours = seconds / 3600;
  long mins = (seconds % 3600) / 60;
  long secs = seconds % 60;

  char buffer[9];  // HH:MM:SS + null terminator
  snprintf(buffer, sizeof(buffer), "%02ld:%02ld:%02ld", hours, mins, secs);
  return string(buffer);
}
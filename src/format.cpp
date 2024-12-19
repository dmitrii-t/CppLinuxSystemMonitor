#include "format.h"

#include <iomanip>
#include <sstream>
#include <string>

using std::setfill;
using std::string;
using std::stringstream;

string Format::ElapsedTime(long elapsed_seconds) {
  long hours = elapsed_seconds / 3600;
  long minutes = (elapsed_seconds % 3600) / 60;
  long seconds = elapsed_seconds % 60;

  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << hours << ":" << std::setw(2)
     << minutes << ":" << std::setw(2) << seconds;

  return ss.str();
}
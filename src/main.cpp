#include "format_test.h"
#include "linux_parser_test.h"
#include "ncurses_display.h"
#include "system.h"
#include "system_test.h"

int main() {
  // Run the tests before starting UI
  // TestLinuxParserAll();
  // TestSystemAll();
  // TestElapsedTimeAll();
  // cout << "LinuxParser: All tests passed!" << '\n';

  // Start the UI
  LinuxParser parser;
  System system{parser};
  NCursesDisplay::Display(system);
}
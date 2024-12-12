#include "linux_parser_test.h"
#include "ncurses_display.h"
#include "system.h"
#include "system_test.h"

int main() {
  // LinuxParser parser;
  // System system{parser};
  // NCursesDisplay::Display(system);
  TestLinuxParser();
  TestSystem();
  cout << "LinuxParser: All tests passed!" << endl;
}
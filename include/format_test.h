#include <cassert>
#include <iostream>

#include "format.h"

using std::cout;

void TestElapsedTimeFormattingHasDoubleZeroes() {
  auto actual = Format::ElapsedTime(604800);
  cout << "Elapsed time: " << actual << '\n';
  assert(actual == "168:00:00");
}

void TestElapsedTimeFormatting() {
  auto actual = Format::ElapsedTime(6400);
  cout << "Elapsed time: " << actual << '\n';
  assert(actual == "01:46:40");
}

void TestElapsedTimeAll() {
  TestElapsedTimeFormattingHasDoubleZeroes();
  TestElapsedTimeFormatting();
}
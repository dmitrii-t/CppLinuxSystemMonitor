#include "processor.h"

#include <cmath>

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() {
  float utilization = ActiveTime() / (1.f * TotalTime());
  return round(100.f * utilization) / 100.f;  // percentage
}

long int Processor::ActiveTime() {
  return user_ + nice_ + system_ + irq_ + softirq_ + steal_ + guest_ +
         guest_nice_;
}

long int Processor::TotalTime() {
  return user_ + nice_ + system_ + idle_ + iowait_ + irq_ + softirq_ + steal_ +
         guest_ + guest_nice_;
}

#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  Processor(long int user, long int nice, long int system, long int idle,
            long int iowait, long int irq, long int softirq, long int steal,
            long int guest, long int guest_nice)
      : user_(user),
        nice_(nice),
        system_(system),
        idle_(idle),
        iowait_(iowait),
        irq_(irq),
        softirq_(softirq),
        steal_(steal),
        guest_(guest),
        guest_nice_(guest_nice) {}

  Processor() {}

  float Utilization();  // DONE: See src/processor.cpp
  long int ActiveTime();
  long int TotalTime();

  // DONE: Declare any necessary private members
 private:
  long int user_;
  long int nice_;
  long int system_;
  long int idle_;
  long int iowait_;
  long int irq_;
  long int softirq_;
  long int steal_;
  long int guest_;
  long int guest_nice_;
};

#endif
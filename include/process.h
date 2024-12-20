#ifndef PROCESS_H
#define PROCESS_H

#include <unistd.h>

#include <string>

using std::string;

const int CLK_TICKS = sysconf(_SC_CLK_TCK);

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid, const string& cmd, int uid, const string& username,
          long int ram, long int user_time, long int system_time,
          long int child_user_time, long int child_system_time,
          long int start_time_sec)
      : pid_(pid),
        cmd_(cmd),
        uid_(uid),
        username_(username),
        ram_(ram),
        user_time_(user_time),
        system_time_(system_time),
        child_user_time_(child_user_time),
        child_system_time_(child_system_time),
        start_time_sec_(start_time_sec) {}

  int Pid();                               // See src/process.cpp
  string User();                           // See src/process.cpp
  string Command();                        // See src/process.cpp
  float CpuUtilization() const;            // See src/process.cpp
  string Ram();                            // See src/process.cpp
  long int UpTime() const;                 // See src/process.cpp
  bool operator>(Process const& a) const;  // See src/process.cpp

 private:
  // Declare any necessary private members
  int pid_;
  string cmd_;
  int uid_;
  string username_;
  long int ram_;
  long int user_time_;
  long int system_time_;
  long int child_user_time_;
  long int child_system_time_;
  long int start_time_sec_;
};

#endif
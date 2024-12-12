#ifndef PROCESS_H
#define PROCESS_H

#include <unistd.h>

#include <string>

using std::string;

const int HERTZ = sysconf(_SC_CLK_TCK);

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid, const string& cmd, int uid, const string& username,
          const string& ram, long int user_time, long int system_time,
          long int child_user_time, long int child_system_time,
          long int start_time, long int uptime)
      : pid_(pid),
        cmd_(cmd),
        uid_(uid),
        username_(username),
        ram_(ram),
        user_time_(user_time),
        system_time_(system_time),
        child_user_time_(child_user_time),
        child_system_time_(child_system_time),
        start_time_(start_time),
        uptime_(uptime) {}

  int Pid();                               // TODO: See src/process.cpp
  string User();                           // TODO: See src/process.cpp
  string Command();                        // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  string Ram();                            // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

 private:
  // TODO: Declare any necessary private members
  int pid_;
  string cmd_;
  int uid_;
  string username_;
  string ram_;
  long int user_time_;
  long int system_time_;
  long int child_user_time_;
  long int child_system_time_;
  long int start_time_;
  long int uptime_;
};

#endif
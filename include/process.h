#ifndef PROCESS_H
#define PROCESS_H

#include <string>

using std::string;
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid, string user, float cpu, string ram, long int time, string command);
  int Pid() const;                               // TODO: See src/process.cpp
  string User() const;                      // TODO: See src/process.cpp
  string Command() const;                   // TODO: See src/process.cpp
  float CpuUtilization() const;            // TODO: See src/process.cpp
  string Ram() const;                       // TODO: See src/process.cpp
  long int UpTime() const;                       // TODO: See src/process.cpp
  bool operator<(Process const & a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
  int pid_;
  string user_;
  float cpu_;
  string ram_;
  long int time_;
  string command_;
};

#endif
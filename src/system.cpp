#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::cout;
using std::set;
using std::size_t;
using std::string;
using std::vector;
using std::stoi;
using std::to_string;
using std::sort;
using std::less;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
  vector<int> pids = LinuxParser::Pids();
  for (int pid : pids) {
    string command = LinuxParser::Command(pid);
    long int time = LinuxParser::UpTime(pid);
    string user = LinuxParser::User(pid);
    string ram = LinuxParser::Ram(pid);
    float cpu = LinuxParser::CpuUtilization(pid);
    Process process{pid, user, cpu, ram, time, command};
    processes_.push_back(process);
  }
  sort(processes_.begin(), processes_.end(), less<Process>()); 
  return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses();}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses();  }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() {
  long int time =  LinuxParser::UpTime(); 
  return time;
}

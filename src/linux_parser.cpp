#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::stoi;
using std::stol;
using std::string;
using std::to_string;
using std::vector;
using std::ifstream;
using std::getline;
using std::istringstream;
using std::to_string;
using std::replace;
using std::cout;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  float memTotal, memFree;
  string line;
  string key;
  float value;
  ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while(getline(filestream, line)) {
      istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
          memTotal = value;
        } else if (key == "MemFree:") {
          memFree = value;
        } 
      }
    }
  }
  return (memTotal - memFree) / memTotal;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long uptime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
  return uptime;
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string line;
  string value;
  vector<string> values;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if(filestream.is_open()) {
    getline(filestream, line);
    istringstream linestream(line);
    while(linestream >> value)
    if (value != "cpu") {
      values.push_back(value);
    }
  }
  return values;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string key;
  int value;
  string line;
  ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (getline(filestream, line)) {
      istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          return value;
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string key;
  int value;
  string line;
  ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (getline(filestream, line)) {
      istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          return value;
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string line, command;
  ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    while (getline(filestream, line)) {
      istringstream linestream(line);
      linestream >> command;
      return command;
    }
  }
  return command;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line, key, memUtil;
  ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (getline(filestream, line)) {
      istringstream linestream(line);
      while (linestream >> key >> memUtil) {
        if (key == "VmSize:") {
          return to_string(stoi(memUtil) / 1000);
        }
      }
    }
  }  
  return memUtil;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line, key, uid;
  ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (getline(filestream, line)) {
      istringstream linestream(line);
      while (linestream >> key >> uid) {
        if (key == "Uid:") {
          return uid;
        }
      }
    }
  }  
  return uid;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string uid = LinuxParser::Uid(pid);
  string line, name, variable, supposedUid;
  ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (getline(filestream, line)) {
      replace(line.begin(), line.end(), ':', ' ');
      istringstream linestream(line);
      while (linestream >> name >> variable >> supposedUid) {
        if (supposedUid == uid) {
          return name;
        }
      }
    }
  }  
  return name;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  long upTime;
  int const upTimePosition = 21;
  ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  string line;
  if (filestream.is_open()) {
    getline(filestream, line);
    istringstream linestream(line);
    int position = 0;
    while (linestream >> upTime) {
      if (position == upTimePosition) {
        return upTime / sysconf(_SC_CLK_TCK);
      }
      position++;
    }
    
  }
  return upTime;
}

float LinuxParser::CpuUtilization(int pid) {
  long token;
  long utime, stime, cutime, cstime;
  long starttime = LinuxParser::UpTime(pid);
  int const utimePosition = 13;
  int const stimePosition = 14;
  int const cutimePosition = 15;
  int const cstimePosition = 16;
  ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  string line;
  if (filestream.is_open()) {
    getline(filestream, line);
    istringstream linestream(line);
    int position = 0;
    while (linestream >> token) {
      if (position == utimePosition) {
        utime = token;
      } else if(position == stimePosition) {
        stime = token;
      } else if(position == cutimePosition) {
        cutime = token;
      } else if(position == cstimePosition) {
        cstime = token;
      }
      position++;
    }

  }

  long Hertz = sysconf(_SC_CLK_TCK);
  long systemUpTime = LinuxParser::UpTime();
  long totalTime = utime + stime;
  totalTime = totalTime + cutime + cstime;
  long seconds = systemUpTime - (starttime / Hertz);
  return (totalTime / Hertz) / seconds;
}
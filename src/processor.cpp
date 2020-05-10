#include <vector>
#include <string>
#include <iostream>

#include "processor.h"
#include "linux_parser.h"

using std::vector;
using std::string;
using std::stof;
using std::cout;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  utilData = LinuxParser::CpuUtilization();
  vector<float> parsedUtilData;
  for (string data : utilData) {
    parsedUtilData.push_back(stof(data));
  }
  // TODO: refactor
  user = parsedUtilData[0];
  nice = parsedUtilData[1];
  system = parsedUtilData[2];
  idle = parsedUtilData[3];
  iowait = parsedUtilData[4];
  irq = parsedUtilData[5];
  softirq = parsedUtilData[6];
  steal = parsedUtilData[7];
  guest = parsedUtilData[8];
  guest_nice = parsedUtilData[9];
  
  user -= guest;
  nice -= guest_nice;
  idle += iowait;
  system += irq + softirq;
  guest += guest_nice;
  total = user + nice + system + idle + steal + guest; 
  return (total - idle)/total;
}
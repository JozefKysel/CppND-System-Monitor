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
  
// NOTE: i followed this post https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux when calculating the cpu utilization 
  user = user - guest;
  nice = nice - guest_nice;
  idle = idle + iowait;
  system = system + irq + softirq;
  long viralTime = guest + guest_nice;
  long total = user + nice + system + idle + steal + viralTime; 
  return (total - idle)/total;
}
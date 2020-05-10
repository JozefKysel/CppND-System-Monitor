#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <string>
#include <vector>

using std::vector;
using std::string;

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  float total;
  float user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
  vector<string> utilData;
};

#endif
#ifndef FORMAT_H
#define FORMAT_H

#include <string>

namespace Format {
std::string ElapsedTime(long times);  // TODO: See src/format.cpp namespace Format
std::string FormatTime(long timeUnit); 
};


#endif
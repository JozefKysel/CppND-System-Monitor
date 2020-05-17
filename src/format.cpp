#include <string>
#include <iostream>

#include "format.h"

#define HOUR_MIN 60
#define MIN_SEC 60

using std::string;
using std::to_string;
using std::cout;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
  long secondsLeft = seconds % MIN_SEC;
  long minutes = (seconds - secondsLeft) / MIN_SEC;
  long minutesLeft = minutes % HOUR_MIN;
  long hours = (minutes - minutesLeft) / HOUR_MIN;
  return Format::FormatTime(hours % 100) + ":" + Format::FormatTime(minutesLeft) + ":" + Format::FormatTime(secondsLeft);
}

string Format::FormatTime(long timeUnit) {
  string timeString = to_string(timeUnit);
  return (timeString.length() < 2) ? ("0" + timeString) : timeString;
}
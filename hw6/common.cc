#include "common.h"

std::ostream &operator<<(std::ostream &out, const Time time) {
  out << static_cast<int>(time.h) << ":" << static_cast<int>(time.m);
  return out;
}

std::ostream &operator<<(std::ostream &out, const Date date) {
  out << static_cast<int>(date.year) << "/" << static_cast<int>(date.month)
      << "/" << static_cast<int>(date.day);
  return out;
}

#include "date.h"

std::ostream &operator<<(std::ostream &out, const Date date) {
  out << date.year << "/" << static_cast<int>(date.month) << "/"
      << static_cast<int>(date.day);
  return out;
}
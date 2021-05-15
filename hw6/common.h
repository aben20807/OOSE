#ifndef COMMON_H
#define COMMON_H

#include <cstdint>

struct Time {
  int8_t h;
  int8_t m;
};

struct Date {
  int16_t year;
  int8_t mounth;
  int8_t day;
};

#endif /* COMMON_H */

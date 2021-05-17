#ifndef COMMON_H
#define COMMON_H

#include <cstdint>
#include <iostream>

struct Time {
  int8_t h;
  int8_t m;
};
/**
 * @brief Define the output format for Time struct.
 *
 * @param out The output stream.
 * @param time The time that needs to be printed to output stream.
 * @return std::ostream&
 */
std::ostream &operator<<(std::ostream &out, const Time time);

struct Date {
  int16_t year;
  int8_t month;
  int8_t day;
};
/**
 * @brief Define the output format for Date struct.
 *
 * @param out The output stream.
 * @param date The date that needs to be printed to output stream.
 * @return std::ostream&
 */
std::ostream &operator<<(std::ostream &out, const Date date);

#endif /* COMMON_H */

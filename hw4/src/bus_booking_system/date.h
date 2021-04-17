#ifndef DATE_H
#define DATE_H

#include <iostream>

struct Date {
  uint16_t year;
  uint8_t month;
  uint8_t day;
};
/**
 * @brief Define the output format for Date struct.
 *
 * @param out The output stream.
 * @param date The date that needs to be printed to output stream.
 * @return std::ostream&
 */
std::ostream &operator<<(std::ostream &out, const Date date);

#endif /* DATE_H */
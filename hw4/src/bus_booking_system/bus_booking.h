#ifndef BUS_BOOKING_H
#define BUS_BOOKING_H

#include <string>
#include "../booking_framework/abstract_booking.h"
#include "date.h"

class BusBooking : public AbstractBooking {
 public:
  BusBooking(std::string buyer_name, std::string bus_name, int num_of_people,
             Date bus_departure_date);
  std::string get_buyer_name() const;
  std::string get_bus_name() const;
  int get_num_of_people() const;
  Date get_bus_departure_date() const;

 private:
  std::string buyer_name_{""};
  std::string bus_name_{""};
  int num_of_people_{0};
  Date bus_departure_date_{1997, 1, 1};
};

std::ostream &operator<<(std::ostream &out, const BusBooking bus_booking);

#endif /* BUS_BOOKING_H */
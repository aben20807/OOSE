#ifndef BUS_BOOKING_TRANSACTOR_H
#define BUS_BOOKING_TRANSACTOR_H

#include <string>
#include "../booking_framework/abstract_booking_transactor.h"
#include "bus_booking.h"

class BusBookingTransactor : public AbstractBookingTransactor<BusBooking> {
 public:
  BusBookingTransactor(std::string name);
  std::string get_name();
  virtual void PrintBookings() const {};

 protected:
  std::string name_;
};

#endif /* BUS_BOOKING_TRANSACTOR_H */
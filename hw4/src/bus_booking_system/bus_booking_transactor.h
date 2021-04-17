#ifndef BUS_BOOKING_TRANSACTOR_H
#define BUS_BOOKING_TRANSACTOR_H

#include <memory>
#include "../booking_framework/booking_transacting_behavior.h"
// #include "booking_behavior_impl.cc"
#include "bus_booking.h"

using BusBookingTransactingBehaviorPtr =
    std::unique_ptr<BookingTransactingBehavior<BusBooking>>;

class BusBookingTransactor {
 public:
  BusBookingTransactor(std::string name,
                       BusBookingTransactingBehaviorPtr booking_helper);
  std::string get_name();
  virtual void PrintBookings() const {};

 protected:
  std::string name_;
  BusBookingTransactingBehaviorPtr booking_helper_{nullptr};
};

#endif /* BUS_BOOKING_TRANSACTOR_H */
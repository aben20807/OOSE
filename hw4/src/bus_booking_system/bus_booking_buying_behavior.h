#ifndef BUS_BOOKING_BUYING_BEHAVIOR_H
#define BUS_BOOKING_BUYING_BEHAVIOR_H

#include <string>
#include "../booking_framework/booking_buying_behavior.h"
#include "bus_booking.h"

class BusBookingBuyingBehavior : public BookingBuyingBehavior<BusBooking> {
 public:
  BusBookingBuyingBehavior() {}

  /* Hooks */
  void BookingBought() {}
};

#endif /* BUS_BOOKING_BUYING_BEHAVIOR_H */
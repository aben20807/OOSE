#ifndef BUS_BOOKING_SELLING_BEHAVIOR_H
#define BUS_BOOKING_SELLING_BEHAVIOR_H

#include <string>
#include "../booking_framework/booking_selling_behavior.h"
#include "bus_booking.h"

class BusBookingSellingBehavior : public BookingSellingBehavior<BusBooking> {
 public:
  BusBookingSellingBehavior() {}

  /* Hooks */
  void BookingSelled() {}
};

#endif /* BUS_BOOKING_SELLING_BEHAVIOR_H */
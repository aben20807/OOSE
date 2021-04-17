#ifndef BOOKING_SELLING_BEHAVIOR_H
#define BOOKING_SELLING_BEHAVIOR_H

#include <string>
#include "booking_transacting_behavior.h"

template <typename Booking>
class BookingSellingBehavior : public BookingTransactingBehavior<Booking> {
 public:
  BookingSellingBehavior() {}

  /* Hooks */
  void BookingSelled() {}
};

#endif /* BOOKING_SELLING_BEHAVIOR_H */
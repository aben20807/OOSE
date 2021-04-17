#ifndef BOOKING_BUYING_BEHAVIOR_H
#define BOOKING_BUYING_BEHAVIOR_H

#include <string>
#include "booking_transacting_behavior.h"

template <typename Booking>
class BookingBuyingBehavior : public BookingTransactingBehavior<Booking> {
 public:
  BookingBuyingBehavior() {}

  /* Hooks */
  void BookingBought() {}
};

#endif /* BOOKING_BUYING_BEHAVIOR_H */
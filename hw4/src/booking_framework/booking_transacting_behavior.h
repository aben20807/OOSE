#ifndef BOOKING_TRANSACTING_BEHAVIOR_H
#define BOOKING_TRANSACTING_BEHAVIOR_H

#include <memory>
#include <string>
#include <unordered_map>
// #include "abstract_booking.h"

template <typename Booking>
class BookingTransactingBehavior {
 public:
  BookingTransactingBehavior() {}
  void AddBookingTransaction(int booking_index,
                             std::shared_ptr<Booking> booking) {
    held_bookings_.emplace(booking_index, std::move(booking));
    BookingAdded();
  }
  void RemoveBookingTransaction(int booking_index) {
    auto erase_count = held_bookings_.erase(booking_index);

    if (erase_count == 0) {
      BookingEmptyWhenRemoved();
    }
    BookingRemoved();
  }

  std::unordered_map<int, std::shared_ptr<Booking>>& get_held_bookings() {
    return held_bookings_;
  }

  /* Hooks */
  virtual void BookingAdded() {}
  virtual void BookingRemoved() {}
  virtual void BookingEmptyWhenRemoved() {}

 protected:
  std::unordered_map<int, std::shared_ptr<Booking>> held_bookings_;
};

#endif /* BOOKING_TRANSACTING_BEHAVIOR_H */
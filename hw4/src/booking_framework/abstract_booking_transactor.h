#ifndef ABSTRACT_BOOKING_TRANSACTOR_H
#define ABSTRACT_BOOKING_TRANSACTOR_H

#include <memory>
#include <unordered_map>
#include "abstract_booking.h"

template <typename Booking>
class AbstractBookingTransactor {
 public:
  AbstractBookingTransactor() {
    static_assert(
        std::is_base_of<AbstractBooking, Booking>::value,
        "Your customed Booking should be derived from AbstractBooking.");
  }
  void AddBookingTransaction(int booking_index,
                             std::shared_ptr<Booking> booking) {
    held_bookings_.emplace(booking_index, booking);
    this->BookingAdded(booking);
  }
  void RemoveBookingTransaction(int booking_index) {
    auto erase_count = held_bookings_.erase(booking_index);

    if (erase_count == 0) {
      this->BookingEmptyWhenRemoved();
    }
    this->BookingRemoved();
  }

  std::unordered_map<int, std::shared_ptr<Booking>> get_held_bookings() const {
    return held_bookings_;
  }

  /* Hooks */
  virtual void BookingAdded(std::shared_ptr<Booking>) {}
  virtual void BookingRemoved() {}
  virtual void BookingEmptyWhenRemoved() {}

 protected:
  std::unordered_map<int, std::shared_ptr<Booking>> held_bookings_;
};

#endif /* ABSTRACT_BOOKING_TRANSACTOR_H */
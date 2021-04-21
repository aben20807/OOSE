#ifndef ABSTRACT_BOOKING_TRANSACTOR_H
#define ABSTRACT_BOOKING_TRANSACTOR_H

#include <memory>
#include <unordered_map>
#include "abstract_booking.h"

/**
 * @brief Abstract class of booking transactor.
 *
 * @tparam Booking the class name that used to be transacted.
 */
template <typename Booking>
class AbstractBookingTransactor {
 public:
  AbstractBookingTransactor() {
    static_assert(
        std::is_base_of<AbstractBooking, Booking>::value,
        "Your customed Booking should be derived from AbstractBooking.");
  }
  /**
   * @brief Add the booking into held booking list.
   *
   * @param booking_index the unique index.
   * @param booking the shared pointer to the booking object.
   */
  void AddBookingTransaction(int booking_index,
                             std::shared_ptr<Booking> booking) {
    held_bookings_.emplace(booking_index, booking);
    this->BookingAdded(booking);
  }

  /**
   * @brief Remove a booking from the booking list.
   *
   * @param booking_index the index of the booking to be removed.
   */
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
  /**
   * @brief The hook called when a Booking is added.
   *
   * Derived class can override this hook function.
   */
  virtual void BookingAdded(std::shared_ptr<Booking>) {}

  /**
   * @brief The hook called when a Booking is removed.
   *
   * Derived class can override this hook function.
   */
  virtual void BookingRemoved() {}

  /**
   * @brief The hook called when the held booking is empty during calling
   * RemoveBookingTransaction.
   *
   * Derived class can override this hook function.
   */
  virtual void BookingEmptyWhenRemoved() {}

 protected:
  std::unordered_map<int, std::shared_ptr<Booking>> held_bookings_;
};

#endif /* ABSTRACT_BOOKING_TRANSACTOR_H */
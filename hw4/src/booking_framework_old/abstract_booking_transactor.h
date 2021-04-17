#ifndef ABSTRACT_BOOKING_TRANSACTOR
#define ABSTRACT_BOOKING_TRANSACTOR

#include <memory>
#include <string>
#include <unordered_map>
#include "abstract_booking.h"

class AbstractBookingTransactor {
 public:
  AbstractBookingTransactor(std::string);
  void AddBookingTransaction();
  void RemoveBookingTransaction();
  std::string get_name();

  AbstractBookingTransactor(AbstractBookingTransactor&&) = default;
  virtual ~AbstractBookingTransactor() = 0;

 protected:
  std::string _name;  // TODO login info
  std::unordered_map<int, std::shared_ptr<AbstractBooking>> held_bookings;
};

#endif /* ABSTRACT_BOOKING_TRANSACTOR */

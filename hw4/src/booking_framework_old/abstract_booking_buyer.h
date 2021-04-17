#ifndef ABSTRACT_BOOKING_BUYER
#define ABSTRACT_BOOKING_BUYER

#include <string>
#include "abstract_booking_transactor.h"

class AbstractBookingBuyer : public AbstractBookingTransactor {
 public:
  AbstractBookingBuyer(std::string name);
  AbstractBookingBuyer(AbstractBookingBuyer&&) = default;
  virtual ~AbstractBookingBuyer() = 0;
};

#endif /* ABSTRACT_BOOKING_BUYER */
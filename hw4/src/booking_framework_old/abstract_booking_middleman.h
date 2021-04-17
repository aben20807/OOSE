#ifndef ABSTRACT_BOOKING_SELLER
#define ABSTRACT_BOOKING_SELLER

#include <string>
#include "abstract_booking_transactor.h"

class AbstractBookingSeller : public AbstractBookingTransactor {
 public:
  AbstractBookingSeller(std::string);
};

#endif /* ABSTRACT_BOOKING_SELLER */

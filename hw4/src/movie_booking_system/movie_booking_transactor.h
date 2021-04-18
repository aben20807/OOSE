#ifndef MOVIE_BOOKING_TRANSACTOR_H
#define MOVIE_BOOKING_TRANSACTOR_H

#include <string>
#include "../booking_framework/abstract_booking_transactor.h"
#include "movie_booking.h"

class MovieBookingTransactor : public AbstractBookingTransactor<MovieBooking> {
 public:
  MovieBookingTransactor(std::string name);
  std::string get_name();
  virtual void PrintBookings() const = 0;

 protected:
  std::string name_;
};

#endif /* MOVIE_BOOKING_TRANSACTOR_H */
#ifndef AUDIENCE_H
#define AUDIENCE_H

#include <string>
#include "movie_booking.h"
#include "movie_booking_transactor.h"

class Audience : public MovieBookingTransactor {
 public:
  Audience(std::string name);
  void AddBooking(int, std::shared_ptr<MovieBooking>);
  void PrintBookings() const final;

 private:
  /* Hooks */
  void BookingAdded(std::shared_ptr<MovieBooking> b) final;
};

#endif /* AUDIENCE_H */
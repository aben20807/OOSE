#ifndef MOVIE_FOR_BOOKING_H
#define MOVIE_FOR_BOOKING_H

#include <string>
#include "movie_booking.h"
#include "movie_booking_transactor.h"

class MovieShowing : public MovieBookingTransactor {
 public:
  MovieShowing(std::string name, Date showing_date);
  void AddBooking(int, std::shared_ptr<MovieBooking>);
  Date get_showing_date() const;

  /**
   * @brief Overridden function to print audience info from movie's booking
   * list.
   */
  void PrintBookings() const final;

 private:
  /* Custom Hooks */
  void BookingAdded(std::shared_ptr<MovieBooking> b) final;
  Date showing_date_;
};

#endif /* MOVIE_FOR_BOOKING_H */
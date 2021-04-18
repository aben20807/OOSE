#ifndef MOVIE_BOOKING_H
#define MOVIE_BOOKING_H

#include <string>
#include "../booking_framework/abstract_booking.h"
#include "date.h"

class MovieBooking : public AbstractBooking {
 public:
  MovieBooking(std::string buyer_name, std::string movie_name,
               int num_of_people, int seat_number, Date movie_showing_date);
  std::string get_buyer_name() const;
  std::string get_movie_name() const;
  int get_num_of_people() const;
  int get_seat_number() const;
  Date get_movie_showing_date() const;

 private:
  std::string buyer_name_{""};
  std::string movie_name_{""};
  int num_of_people_{0};
  int seat_number_{0};
  Date movie_showing_date_{1997, 1, 1};
};

std::ostream &operator<<(std::ostream &out, const MovieBooking movie_booking);

#endif /* MOVIE_BOOKING_H */
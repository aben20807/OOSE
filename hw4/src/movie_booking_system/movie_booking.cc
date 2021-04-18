#include "movie_booking.h"

MovieBooking::MovieBooking(std::string buyer_name, std::string movie_name,
                           int num_of_people, int seat_number,
                           Date movie_showing_date)
    : buyer_name_{buyer_name},
      movie_name_{movie_name},
      num_of_people_{num_of_people},
      seat_number_{seat_number},
      movie_showing_date_{movie_showing_date} {}

std::string MovieBooking::get_buyer_name() const { return buyer_name_; }
std::string MovieBooking::get_movie_name() const { return movie_name_; }
int MovieBooking::get_num_of_people() const { return num_of_people_; }
int MovieBooking::get_seat_number() const { return seat_number_; }
Date MovieBooking::get_movie_showing_date() const {
  return movie_showing_date_;
}

std::ostream &operator<<(std::ostream &out, const MovieBooking movie_booking) {
  out << "Passenger: " << movie_booking.get_buyer_name()
      << ", Movie: " << movie_booking.get_movie_name()
      << ", Num of people: " << movie_booking.get_num_of_people()
      << ", Seat number: " << movie_booking.get_seat_number()
      << ", Date: " << movie_booking.get_movie_showing_date();
  return out;
}
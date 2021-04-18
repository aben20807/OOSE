#ifndef MOVIE_BOOKING_MACHINE_H
#define MOVIE_BOOKING_MACHINE_H

#include "audience.h"
#include "movie_booking.h"
#include "movie_showing.h"

class MovieBookingMachine {
 public:
  /**
   * @brief Get the Booking Machine object.
   *
   * Because the constructor is private, the way to get booking machine is to
   * use this function.
   * @return MovieBookingMachine&
   */
  static MovieBookingMachine &GetMovieBookingMachine() {
    static MovieBookingMachine instance;
    return instance;
  }
  /**
   * @brief Copy constructor and copy assignment are deleted so that the object
   * cannot be copied.
   */
  MovieBookingMachine(const MovieBookingMachine &) = delete;
  void operator=(const MovieBookingMachine &) = delete;
  /**
   * @brief Add one booking to connect two transactors.
   *
   * Every bookings increase the booking_index_ to make it unique.
   * Shared pointer (shared_ptr) is used to share the booking object to two
   * transactors, and the booking object will be freed automatically if the
   * pointer counter becomes 0.
   * @param audience The pointer to the audience.
   * @param movie The pointer to the movie.
   * @param num_of_people how many seats (number of people) are booked in this
   * action.
   * @param seat_number the specified seat number.
   */
  void MakeBooking(Audience *const audience, MovieShowing *const movie,
                   const int num_of_people, const int seat_number);

 private:
  MovieBookingMachine() {}
  inline static int booking_index_{0};
};

#endif /* MOVIE_BOOKING_MACHINE_H */
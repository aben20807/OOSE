#include <iostream>
#include <memory>
#include "movie_booking_machine.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  /* New people */
  auto alice = std::make_unique<Audience>("Alice");
  auto bob = std::make_unique<Audience>("Bob");
  auto carol = std::make_unique<Audience>("Carol");
  auto dave = std::make_unique<Audience>("Dave");
  auto eve = std::make_unique<Audience>("Eve");
  /* New moviees */
  auto movie100 = std::make_unique<MovieShowing>("Movie100", Date{2021, 2, 25});
  auto movie101 = std::make_unique<MovieShowing>("Movie101", Date{2021, 2, 26});
  auto movie102 = std::make_unique<MovieShowing>("Movie102", Date{2021, 2, 27});
  auto movie103 = std::make_unique<MovieShowing>("Movie103", Date{2022, 2, 28});
  /* Book movie bookings */
  auto &mbmachine = MovieBookingMachine::GetMovieBookingMachine();
  mbmachine.MakeBooking(alice.get(), movie100.get(), /* num_of_pelple */ 4,
                        /* seat_number */ 0);
  mbmachine.MakeBooking(alice.get(), movie102.get(), /* num_of_pelple */ 2,
                        /* seat_number */ 1);
  mbmachine.MakeBooking(bob.get(), movie100.get(), /* num_of_pelple */ 6,
                        /* seat_number */ 2);
  mbmachine.MakeBooking(carol.get(), movie101.get(), /* num_of_pelple */ 3,
                        /* seat_number */ 3);
  mbmachine.MakeBooking(dave.get(), movie100.get(), /* num_of_pelple */ 5,
                        /* seat_number */ 4);
  /* Validation */
  movie100->PrintBookings();
  alice->PrintBookings();
  movie101->PrintBookings();
  bob->PrintBookings();
  movie103->PrintBookings();
  eve->PrintBookings();
  return 0;
}
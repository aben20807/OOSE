#include "movie_booking_machine.h"

/**
 * @brief Adapter to make aggregate struct be shared.
 *
 * @tparam T The type of aggregate struct.
 * @tparam Args The variadic type of args.
 * @param args The in-order elements of aggregate struct.
 * @return std::shared_ptr<T>
 */
template <typename T, typename... Args>
static std::shared_ptr<T> make_aggregate_shared(Args &&... args) {
  return std::make_shared<T>(T{std::forward<Args>(args)...});
}

void MovieBookingMachine::MakeBooking(Audience *const audience,
                                      MovieShowing *const movie,
                                      const int num_of_people,
                                      const int seat_number) {
  auto booking = make_aggregate_shared<MovieBooking>(
      audience->get_name(), movie->get_name(), num_of_people, seat_number,
      movie->get_showing_date());
  audience->AddBooking(booking_index_, booking);
  movie->AddBooking(booking_index_, booking);
  booking_index_++;
}
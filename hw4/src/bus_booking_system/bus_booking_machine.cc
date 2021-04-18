#include "bus_booking_machine.h"

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

void BusBookingMachine::MakeBooking(Passenger *const passenger,
                                    BusForBooking *const bus,
                                    const int num_of_people) {
  auto booking = make_aggregate_shared<BusBooking>(
      passenger->get_name(), bus->get_name(), num_of_people,
      bus->get_departure_date());
  passenger->AddBooking(booking_index_, booking);
  bus->AddBooking(booking_index_, booking);
  booking_index_++;
}
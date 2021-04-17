#ifndef BUS_BOOKING_MACHINE_H
#define BUS_BOOKING_MACHINE_H

#include "bus_booking.h"
#include "bus_for_booking.h"
#include "passenger.h"

/**
 * @brief Adapter to make aggregate struct be shared.
 *
 * @tparam T The type of aggregate struct.
 * @tparam Args The variadic type of args.
 * @param args The in-order elements of aggregate struct.
 * @return std::shared_ptr<T>
 */
template <typename T, typename... Args>
std::shared_ptr<T> make_aggregate_shared(Args &&... args) {
  return std::make_shared<T>(T{std::forward<Args>(args)...});
}

class BusBookingMachine {
 public:
  /**
   * @brief Get the Booking Machine object.
   *
   * Because the constructor is private, the way to get booking machine is to
   * use this function.
   * @return BusBookingMachine&
   */
  static BusBookingMachine &GetBusBookingMachine() {
    static BusBookingMachine instance;
    return instance;
  }
  /**
   * @brief Copy constructor and copy assignment are deleted so that the object
   * cannot be copied.
   */
  BusBookingMachine(const BusBookingMachine &) = delete;
  void operator=(const BusBookingMachine &) = delete;
  /**
   * @brief Add one booking to connect two transactors.
   *
   * Every bookings increase the booking_index_ to make it unique.
   * Shared pointer (shared_ptr) is used to share the booking object to two
   * transactors, and the booking object will be freed automatically if the
   * pointer counter becomes 0.
   * @param passenger The pointer to the passenger.
   * @param bus The pointer to the bus.
   * @param num_of_people how many seats (number of people) are booked in this
   * action.
   */
  void MakeBooking(Passenger *const passenger, BusForBooking *const bus,
                   const int num_of_people) {
    auto booking = make_aggregate_shared<BusBooking>(
        passenger->get_name(), bus->get_name(), num_of_people,
        bus->get_departure_date());
    passenger->AddBooking(booking_index_, booking);
    bus->AddBooking(booking_index_, booking);
    booking_index_++;
  }

 private:
  BusBookingMachine() {}
  inline static int booking_index_{0};
};

#endif /* BUS_BOOKING_MACHINE_H */
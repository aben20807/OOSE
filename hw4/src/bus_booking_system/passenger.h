#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>

#include "bus_booking.h"
#include "bus_booking_buying_behavior.h"
// template class BookingBuyingBehavior<BusBooking>;
// #include "booking_behavior_impl.cc"
//
#include "bus_booking_transactor.h"

class Passenger : public BusBookingTransactor {
 public:
  Passenger(std::string name);
  void AddBooking(int, std::shared_ptr<BusBooking>);
  void PrintBookings() const override;

  // Passenger(Passenger&&) = default;
  // ~Passenger() override{};
 private:
};

#endif /* PASSENGER_H */
#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
#include "bus_booking.h"
#include "bus_booking_transactor.h"

class Passenger : public BusBookingTransactor {
 public:
  Passenger(std::string name);
  void AddBooking(int, std::shared_ptr<BusBooking>);
  void PrintBookings() const override;

 private:
  /* Hooks */
  void BookingAdded(std::shared_ptr<BusBooking> b) final;
};

#endif /* PASSENGER_H */
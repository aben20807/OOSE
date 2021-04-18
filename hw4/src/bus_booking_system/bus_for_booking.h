#ifndef BUS_FOR_BOOKING_H
#define BUS_FOR_BOOKING_H

#include <string>
#include "bus_booking.h"
#include "bus_booking_transactor.h"

class BusForBooking : public BusBookingTransactor {
 public:
  BusForBooking(std::string name, Date departure_date);
  void AddBooking(int, std::shared_ptr<BusBooking>);
  Date get_departure_date() const;
  void PrintBookings() const override;

 private:
  /* Hooks */
  void BookingAdded(std::shared_ptr<BusBooking> b) final;
  Date departure_date_;
};

#endif /* BUS_FOR_BOOKING_H */
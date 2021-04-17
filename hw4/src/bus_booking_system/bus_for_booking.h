#ifndef BUS_FOR_BOOKING_H
#define BUS_FOR_BOOKING_H

#include <string>
// #include "../booking_framework/booking_selling_behavior.h"
#include "bus_booking.h"
#include "bus_booking_selling_behavior.h"
// template class BookingSellingBehavior<BusBooking>;
// #include "booking_behavior_impl.cc"

#include "bus_booking_transactor.h"

class BusForBooking : public BusBookingTransactor {
 public:
  BusForBooking(std::string name, Date departure_date);
  void AddBooking(int, std::shared_ptr<BusBooking>);
  Date get_departure_date() const;
  void PrintBookings() const override;

 private:
  Date departure_date_;
};

#endif /* BUS_FOR_BOOKING_H */
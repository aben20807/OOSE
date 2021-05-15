#ifndef SPECIFIC_FLIGHT_H
#define SPECIFIC_FLIGHT_H

#include <vector>

#include "booking.h"
#include "common.h"

class RegularFlight;
class EmployeeRole;

class SpecificFlight {
 public:
  void addBooking(Booking* booking) {
    bookings.emplace_back(booking);
    booking->linkSpecificFlight(this);
  }
  void linkRegularFlight(RegularFlight* regular_flight) {
    this->regular_flight = regular_flight;
  }
  void addEmployeeRole(EmployeeRole* emp) { this->employees.push_back(emp); }

 private:
  Date date;
  std::vector<Booking*> bookings{};
  std::vector<EmployeeRole*> employees{};
  RegularFlight* regular_flight{nullptr};
};

#endif /* SPECIFIC_FLIGHT_H */

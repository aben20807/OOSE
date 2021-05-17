#ifndef SPECIFIC_FLIGHT_H
#define SPECIFIC_FLIGHT_H

#include <vector>

#include "booking.h"
#include "common.h"
#include "regular_flight.h"

class EmployeeRole;

class SpecificFlight {
 public:
  SpecificFlight(Date date, RegularFlight* regular_flight) : date{date} {
    linkRegularFlight(regular_flight);
  }
  Date getDate() const { return date; }
  void addBooking(Booking* booking) {
    bookings.emplace_back(booking);
    booking->linkSpecificFlight(this);
  }
  void linkRegularFlight(RegularFlight* regular_flight) {
    this->regular_flight = regular_flight;
    regular_flight->addSpecificFlight(this);
  }
  void addEmployeeRole(EmployeeRole* emp) { this->employees.push_back(emp); }

 private:
  Date date;
  std::vector<Booking*> bookings{};
  std::vector<EmployeeRole*> employees{};
  RegularFlight* regular_flight{nullptr};
};

#endif /* SPECIFIC_FLIGHT_H */

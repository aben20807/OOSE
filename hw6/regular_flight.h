#ifndef REGULAR_FLIGHT_H
#define REGULAR_FLIGHT_H

#include <vector>

#include "common.h"
#include "specific_flight.h"

class Airline;

class RegularFlight {
 public:
  RegularFlight(Time time, int flightNumber)
      : time{time}, flightNumber{flightNumber} {}
  RegularFlight(Time time, int flightNumber, Airline* airline)
      : RegularFlight(time, flightNumber) {
    linkAirline(airline);
  }
  void addSpecificFlight(SpecificFlight* specific_flight) {
    specific_flights.emplace_back(specific_flight);
    specific_flight->linkRegularFlight(this);
  }
  void linkAirline(Airline* airline) { this->airline = airline; }

 private:
  Time time;
  int flightNumber;
  std::vector<SpecificFlight*> specific_flights{};
  Airline* airline{nullptr};
};

#endif /* REGULAR_FLIGHT_H */

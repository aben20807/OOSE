#ifndef REGULAR_FLIGHT_H
#define REGULAR_FLIGHT_H

#include <vector>

#include "airline.h"
#include "common.h"

class SpecificFlight;

class RegularFlight {
 public:
  RegularFlight(Time time, int flightNumber, Airline* airline)
      : time{time}, flightNumber{flightNumber} {
    linkAirline(airline);
  }
  std::vector<SpecificFlight*>& getSpecificFlights() {
    return specific_flights;
  }
  Time getTime() const { return time; }
  int getFlightNumber() const { return flightNumber; }
  void addSpecificFlight(SpecificFlight* specific_flight) {
    specific_flights.emplace_back(specific_flight);
  }
  void linkAirline(Airline* airline) {
    this->airline = airline;
    airline->addRegularFlight(this);
  }

 private:
  Time time;
  int flightNumber;
  std::vector<SpecificFlight*> specific_flights{};
  Airline* airline{nullptr};
};

#endif /* REGULAR_FLIGHT_H */

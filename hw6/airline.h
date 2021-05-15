#ifndef AIRLINE_H
#define AIRLINE_H

#include <string>
#include <vector>

#include "person.h"
#include "regular_flight.h"

class Airline {
 public:
  Airline(std::string name) : name{name} {}
  void addPerson(Person* person) {
    people.emplace_back(person);
    person->linkAirline(this);
  }
  void addRegularFlight(RegularFlight* reg_flight) {
    flights.emplace_back(reg_flight);
    reg_flight->linkAirline(this);
  }

 private:
  std::string name;
  std::vector<Person*> people{};
  std::vector<RegularFlight*> flights{};
};

#endif /* AIRLINE_H */

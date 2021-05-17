#ifndef AIRLINE_H
#define AIRLINE_H

#include <string>
#include <vector>

class Person;
class RegularFlight;

class Airline {
 public:
  Airline(std::string name) : name{name} {}
  void addPerson(Person* person) { people.emplace_back(person); }
  void addRegularFlight(RegularFlight* reg_flight) {
    flights.emplace_back(reg_flight);
  }
  std::vector<RegularFlight*>& getRegularFlights() { return flights; }
  std::vector<Person*>& getPeople() { return people; }

 private:
  std::string name;
  std::vector<Person*> people{};
  std::vector<RegularFlight*> flights{};
};

#endif /* AIRLINE_H */

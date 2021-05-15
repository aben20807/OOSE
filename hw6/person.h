#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <vector>

#include "person_role.h"
class Airline;

class Person {
 public:
  Person(std::string name, std::string idNumber)
      : name{name}, idNumber{idNumber} {}
  std::string get_name() const { return name; }
  std::string getIdNumber() const { return idNumber; }
  void addPersonRole(PersonRole* person_role) {
    if (roles.size() > 2) {
      std::cerr << "PersonRole should not more than 2\n";
      return;
    }
    roles.push_back(person_role);
    person_role->linkPerson(this);
  }
  void linkAirline(Airline* airline) { this->airline = airline; }

 private:
  std::string name;
  std::string idNumber;
  std::vector<PersonRole*> roles{};
  Airline* airline{nullptr};
};

#endif /* PERSON_H */

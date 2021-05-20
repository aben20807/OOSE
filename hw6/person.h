#ifndef PERSON_H
#define PERSON_H

#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

#include "airline.h"
#include "employee_role.h"
#include "passenger_role.h"
#include "person_role.h"
#include "specific_flight.h"

class Person {
 public:
  Person(std::string name, std::string idNumber, Airline* airline,
         std::initializer_list<PersonRole*> roles)
      : name{name}, idNumber{idNumber} {
    if (airline != nullptr) {
      linkAirline(airline);
    }
    for (auto& p : roles) {
      this->addPersonRole(p);
    }
  }
  Person(std::string name, std::string idNumber)
      : Person{name, idNumber, nullptr, {}} {}
  Person(std::string name, std::string idNumber,
         std::initializer_list<PersonRole*> roles)
      : Person{name, idNumber, nullptr, roles} {}
  ~Person() {
    for (auto& p : roles) {
      delete p;
    }
  }
  std::string getName() const { return name; }
  std::string getIdNumber() const { return idNumber; }
  EmployeeRole* get_employee_role() {
    for (auto role : roles) {
      EmployeeRole* emp = dynamic_cast<EmployeeRole*>(role);
      if (emp != nullptr) {
        return emp;
      }
    }
    std::cerr << name << " does not have an EmployeeRole\n";
    return nullptr;
  }
  PassengerRole* get_passenger_role() {
    for (auto role : roles) {
      PassengerRole* pas = dynamic_cast<PassengerRole*>(role);
      if (pas != nullptr) {
        return pas;
      }
    }
    std::cerr << name << " does not have an EmployeeRole\n";
    return nullptr;
  }
  void addPersonRole(PersonRole* person_role) {
    if (roles.size() > 2) {
      std::cerr << "PersonRole should not more than 2\n";
      return;
    }
    roles.push_back(person_role);
    person_role->linkPerson(this);
  }
  void linkAirline(Airline* airline) {
    this->airline = airline;
    airline->addPerson(this);
  }

 private:
  std::string name;
  std::string idNumber;
  std::vector<PersonRole*> roles{};
  Airline* airline{nullptr};
};

#endif /* PERSON_H */

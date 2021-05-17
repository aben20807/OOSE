#ifndef EMPLOYEE_ROLE_H
#define EMPLOYEE_ROLE_H

#include <iostream>
#include <vector>

#include "person_role.h"
#include "specific_flight.h"

class EmployeeRole : public PersonRole {
 public:
  EmployeeRole(std::string jobFunction) : jobFunction{jobFunction} {}
  EmployeeRole(std::string jobFunction, EmployeeRole* supervisor)
      : EmployeeRole{jobFunction} {
    addSupervisor(supervisor);
  }
  void perfomJobFunction() { std::cout << jobFunction << "\n"; }
  void addSubordinate(EmployeeRole* emp) {
    subordinates.emplace_back(emp);
    emp->linkSupervisor(emp);
  }
  void addSupervisor(EmployeeRole* emp) { emp->addSubordinate(this); }
  void linkSupervisor(EmployeeRole* emp) { this->supervisor = emp; }
  void addSpecificFlight(SpecificFlight* specific_flight) {
    this->specific_flights.push_back(specific_flight);
    specific_flight->addEmployeeRole(this);
  }
  std::vector<EmployeeRole*>& getSubordinates() { return subordinates; }

 private:
  std::string jobFunction{""};
  EmployeeRole* supervisor{nullptr};
  std::vector<EmployeeRole*> subordinates{};
  std::vector<SpecificFlight*> specific_flights{};
};

#endif /* EMPLOYEE_ROLE_H */

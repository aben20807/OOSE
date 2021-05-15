#ifndef EMPLOYEE_ROLE_H
#define EMPLOYEE_ROLE_H

#include <iostream>
#include <vector>

#include "person_role.h"
#include "specific_flight.h"

class EmployeeRole : public PersonRole {
 public:
  void perfomJobFunction() { this->jobFunction(); }
  void addSubordinate(EmployeeRole* emp) {
    subordinates.emplace_back(emp);
    emp->linkSupervisor(emp);
  }
  void linkSupervisor(EmployeeRole* emp) { this->supervisor = emp; }
  void addSpecificFlight(SpecificFlight* specific_flight) {
    this->specific_flights.push_back(specific_flight);
    specific_flight->addEmployeeRole(this);
  }

 private:
  void jobFunction() { std::cout << "doing job...\n"; }
  EmployeeRole* supervisor{nullptr};
  std::vector<EmployeeRole*> subordinates{};
  std::vector<SpecificFlight*> specific_flights{};
};

#endif /* EMPLOYEE_ROLE_H */

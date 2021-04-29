#ifndef OFFICE_H
#define OFFICE_H

#include <vector>

#include "common.h"
#include "employee.h"

class Office {
 public:
  Office(std::string name) : name_{name} {}
  std::string get_name() const { return name_; }
  void AddEmployee(Employee* e) {
    allocated_to_.emplace_back(e);
    e->set_office(this);
  }

 private:
  std::string name_;
  std::vector<const Employee*> allocated_to_{};
};

#endif
#ifndef COMPANY_H
#define COMPANY_H

#include <string>
#include <vector>
#include "common.h"
#include "employee.h"

class Company {
 public:
  Company(std::string name, std::string unified_business_number)
      : name_{name}, unified_business_number_{unified_business_number} {}
  std::string get_name() const { return name_; }
  std::string get_unified_business_number() const {
    return unified_business_number_;
  }
  void AddEmployee(Employee *e) {
    employees_.emplace_back(e);
    e->set_workfor(this);
  }
  std::size_t get_num_of_employees() const { return employees_.size(); }

  std::vector<const Employee *> Filter(std::string name) {
    std::vector<const Employee *> ret;
    for (const Employee *e : employees_)
      if (e->get_name() == name) ret.emplace_back(e);
    return ret;
  }

  std::vector<const Employee *> Filter(int id) {
    std::vector<const Employee *> ret;
    for (const Employee *e : employees_)
      if (e->get_id() == id) ret.emplace_back(e);
    return ret;
  }

  std::vector<const Employee *> Filter(Gender gender) {
    std::vector<const Employee *> ret;
    for (const Employee *e : employees_)
      if (e->get_gender() == gender) ret.emplace_back(e);
    return ret;
  }

  std::vector<const Employee *> Filter(Position position) {
    std::vector<const Employee *> ret;
    for (const Employee *e : employees_)
      if (e->get_position() == position) ret.emplace_back(e);
    return ret;
  }

 private:
  std::string name_;
  std::string unified_business_number_;
  std::vector<const Employee *> employees_{};
};

#endif /* COMPANY_H */
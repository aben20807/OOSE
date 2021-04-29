#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

#include "common.h"
#include "person.h"

class Company;
class Office;

class Employee : public Person {
 public:
  Employee(std::string name, Gender gender, int id, Position position)
      : Person{name, gender}, id_{id}, position_{position} {}
  int get_id() const { return id_; }
  Position get_position() const { return position_; }
  void set_workfor(Company *c) { workfor_ = c; }
  const Company *get_workfor() const { return workfor_; }
  void set_office(Office *o) { office = o; }
  const Office *get_office() const { return office; }
  virtual ~Employee() = default;

 protected:
  int id_;
  Position position_;
  const Company *workfor_{nullptr};
  const Office *office{nullptr};
};

#endif /* EMPLOYEE_H */
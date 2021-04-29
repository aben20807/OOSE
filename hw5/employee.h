#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include "common.h"

class Company;

class Employee {
 public:
  Employee(std::string name, int id, Gender gender, Position position)
      : name_{name}, id_{id}, gender_{gender}, position_{position} {}
  std::string get_name() const { return name_; }
  int get_id() const { return id_; }
  Gender get_gender() const { return gender_; }
  Position get_position() const { return position_; }
  void set_workfor(Company *c) { workfor_ = c; }
  Company *get_workfor() const { return workfor_; }
  virtual ~Employee() = default;

 protected:
  std::string name_;
  int id_;
  Gender gender_;
  Position position_;
  Company *workfor_{nullptr};
};

#endif /* EMPLOYEE_H */
#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <vector>

#include "common.h"
#include "employee.h"

class AdministrativeAssistant;

class Manager : public Employee {
 public:
  Manager(std::string name, Gender gender, int id)
      : Employee{name, gender, id, Position::Manager} {}
  void AddSubordinate(AdministrativeAssistant* a) {
    subordinates_.emplace_back(a);
  }
  std::vector<const AdministrativeAssistant*> get_subordinates() const {
    return subordinates_;
  }

 private:
  std::vector<const AdministrativeAssistant*> subordinates_{};
};

#endif /* MANAGER_H */
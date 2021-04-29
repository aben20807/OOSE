#ifndef ADMINISTRATIVE_ASSISTANT_H
#define ADMINISTRATIVE_ASSISTANT_H

#include <string>
#include <vector>
#include "common.h"
#include "employee.h"
#include "manager.h"

class Manager;

class AdministrativeAssistant : public Employee {
 public:
  AdministrativeAssistant(std::string name, int id, Gender gender,
                          Manager* supervisor)
      : Employee(name, id, gender, Position::AdministrativeAssistant),
        supervisors_{supervisor} {
    supervisor->AddSubordinate(this);
  }
  void AddSupervisor(Manager* supervisor) {
    supervisors_.emplace_back(supervisor);
    supervisor->AddSubordinate(this);
  }
  std::vector<Manager*> get_supervisors() const { return supervisors_; }

 private:
  std::vector<Manager*> supervisors_;
};

#endif /* ADMINISTRATIVE_ASSISTANT_H */
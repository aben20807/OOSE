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
  AdministrativeAssistant(std::string name, Gender gender, int id,
                          Manager* supervisor)
      : Employee{name, gender, id, Position::AdministrativeAssistant},
        supervisors_{supervisor} {
    supervisor->AddSubordinate(this);
  }
  void AddSupervisor(Manager* supervisor) {
    supervisors_.emplace_back(supervisor);
    supervisor->AddSubordinate(this);
  }
  std::vector<const Manager*> get_supervisors() const { return supervisors_; }

 private:
  std::vector<const Manager*> supervisors_;
};

#endif /* ADMINISTRATIVE_ASSISTANT_H */